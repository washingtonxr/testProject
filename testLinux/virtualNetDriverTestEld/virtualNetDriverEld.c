#undef PDEBUG             /* undef it, just in case */
#ifdef SNULL_DEBUG
#  ifdef __KERNEL__
     /* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "snull: " fmt, ## args)
#  else
     /* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif
#undef PDEBUGG
#define PDEBUGG(fmt, args...) /* nothing: it's a placeholder */

/* These are the flags in the statusword */
#define SNULL_RX_INTR 0x0001
#define SNULL_TX_INTR 0x0002
/* Default timeout period */
#define SNULL_TIMEOUT 6   /* In jiffies */
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/in6.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>

static int lockup = 0;
static int timeout = SNULL_TIMEOUT;
struct net_device snull_devs[2];//这里定义两个设备，一个是snull0,一个是snull1
//网络设备结构体,作为net_device->priv
struct snull_priv {
    struct net_device_stats stats;//有用的统计信息
    int status;//网络设备的状态信息，是发完数据包，还是接收到网络数据包
    int rx_packetlen;//接收到的数据包长度
    u8 *rx_packetdata;//接收到的数据
    int tx_packetlen;//发送的数据包长度
    u8 *tx_packetdata;//发送的数据
    struct sk_buff *skb;//socket buffer结构体，网络各层之间传送数据都是通过这个结构体来实现的
    spinlock_t lock;//自旋锁
};

void snull_tx_timeout (struct net_device *dev);

//网络接口的打开函数
int snull_open(struct net_device *dev)
 {
    printk("call snull_open/n");
    memcpy(dev->dev_addr, "/0SNUL0", ETH_ALEN);//分配一个硬件地址，ETH＿ALEN是网络设备硬件地址的长度
  
    netif_start_queue(dev);//打开传输队列，这样才能进行数据传输

    return 0;
}
int snull_release(struct net_device *dev)
{
    printk("call snull_release/n");
    netif_stop_queue(dev); //当网络接口关闭的时候，调用stop方法，这个函数表示不能再发送数据
    return 0;
}

//接包函数
void snull_rx(struct net_device *dev, int len, unsigned char *buf)
{
  
    struct sk_buff *skb;
    struct snull_priv *priv = (struct snull_priv *) dev->priv;
 
    /*
     * The packet has been retrieved from the transmission
     * medium. Build an skb around it, so upper layers can handle it
     */


    skb = dev_alloc_skb(len+2);//分配一个socket buffer,并且初始化skb->data,skb->tail和skb->head
    if (!skb) {
        printk("snull rx: low on mem - packet dropped/n");
        priv->stats.rx_dropped++;
        return;
    }
    skb_reserve(skb, 2); /* align IP on 16B boundary */
    memcpy(skb_put(skb, len), buf, len);//skb_put是把数据写入到socket buffer
    /* Write metadata, and then pass to the receive level */
    skb->dev = dev;
    skb->protocol = eth_type_trans(skb, dev);//返回的是协议号
    skb->ip_summed = CHECKSUM_UNNECESSARY; //此处不校验
    priv->stats.rx_packets++;//接收到包的个数＋1
   
    priv->stats.rx_bytes += len;//接收到包的长度
    netif_rx(skb);//通知内核已经接收到包，并且封装成socket buffer传到上层
    return;
}
  
      
/*
 * The typical interrupt entry point
 */
//中断处理，此程序中没有硬件，因此，没有真正的硬件中断，只是模拟中断，在发送完网络数据包之后，会产生中断
//用来通知内核已经发送完数据包，当新的数据包到达网络接口时，会发生中断，通知新的数据包已经到来了
void snull_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
 
    int statusword;//用来标识是发送完毕还是接收到新的数据包
    struct snull_priv *priv;
    /*
     * As usual, check the "device" pointer for shared handlers.
     * Then assign "struct device *dev"
     */
    struct net_device *dev = (struct net_device *)dev_id;
    /* ... and check with hw if it's really ours */
    if (!dev /*paranoid*/ ) return;
    /* Lock the device */
    priv = (struct snull_priv *) dev->priv;
    spin_lock(&priv->lock);
    /* retrieve statusword: real netdevices use I/O instructions */
    statusword = priv->status;
    if (statusword & SNULL_RX_INTR) {//如果是接收
        /* send it to snull_rx for handling */
        snull_rx(dev, priv->rx_packetlen, priv->rx_packetdata);
    }
    if (statusword & SNULL_TX_INTR) {//如果发送完毕
        /* a transmission is over: free the skb */
        priv->stats.tx_packets++;
        priv->stats.tx_bytes += priv->tx_packetlen;
        dev_kfree_skb(priv->skb);//释放skb 套接字缓冲区
    }
    /* Unlock the device and we are done */
    spin_unlock(&priv->lock);
    return;
}

/*
 * Transmit a packet (low level interface)
 */
//真正的处理的发送数据包
//模拟从一个网络向另一个网络发送数据包
void snull_hw_tx(char *buf, int len, struct net_device *dev)

{
 
 
   /*
     * This function deals with hw details. This interface loops
     * back the packet to the other snull interface (if any).
     * In other words, this function implements the snull behaviour,
     * while all other procedures are rather device-independent
     */
    struct iphdr *ih;//ip头部
    struct net_device *dest;//目标设备结构体，net_device存储一个网络接口的重要信息，是网络驱动程序的核心
    struct snull_priv *priv;
    u32 *saddr, *daddr;//源设备地址与目标设备地址
    /* I am paranoid. Ain't I? */
    if (len < sizeof(struct ethhdr) + sizeof(struct iphdr)) {
        printk("snull: Hmm... packet too short (%i octets)/n",
               len);
        return;
    }

    /*
     * Ethhdr is 14 bytes, but the kernel arranges for iphdr
     * to be aligned (i.e., ethhdr is unaligned)
     */
    ih = (struct iphdr *)(buf+sizeof(struct ethhdr));
    saddr = &ih->saddr;
    daddr = &ih->daddr;
//在同一台机器上模拟两个网络，不同的网段地址，进行发送网络数据包与接收网络数据包
    ((u8 *)saddr)[2] ^= 1; /* change the third octet (class C) ^是位异或操作符把第三个部分的网络地址与1进行异或，由于同一网络的数据不进行转发*/
    ((u8 *)daddr)[2] ^= 1;
    ih->check = 0;         /* and rebuild the checksum (ip needs it) */
    ih->check = ip_fast_csum((unsigned char *)ih,ih->ihl);
    if (dev == snull_devs)
        PDEBUGG("%08x:%05i --> %08x:%05i/n",
               ntohl(ih->saddr),ntohs(((struct tcphdr *)(ih+1))->source),
               ntohl(ih->daddr),ntohs(((struct tcphdr *)(ih+1))->dest));
    else
        PDEBUGG("%08x:%05i <-- %08x:%05i/n",
               ntohl(ih->daddr),ntohs(((struct tcphdr *)(ih+1))->dest),
               ntohl(ih->saddr),ntohs(((struct tcphdr *)(ih+1))->source));

    /*
     * Ok, now the packet is ready for transmission: first simulate a
     * receive interrupt on the twin device, then  a
     * transmission-done on the transmitting device
     */
    dest = snull_devs + (dev==snull_devs ? 1 : 0);//如果dev是0，那么dest就是1,如果dev是1，那么dest是0
    priv = (struct snull_priv *) dest->priv;//目标dest中的priv
    priv->status = SNULL_RX_INTR;
    priv->rx_packetlen = len;
    priv->rx_packetdata = buf;
    snull_interrupt(0, dest, NULL);
    priv = (struct snull_priv *) dev->priv;
    priv->status = SNULL_TX_INTR;
    priv->tx_packetlen = len;
    priv->tx_packetdata = buf;
    if (lockup && ((priv->stats.tx_packets + 1) % lockup) == 0) {
        /* Simulate a dropped transmit interrupt */
        netif_stop_queue(dev);

 
        PDEBUG("Simulate lockup at %ld, txp %ld/n", jiffies,
                        (unsigned long) priv->stats.tx_packets);
    }
    else
        snull_interrupt(0, dev, NULL);
}
 

/*
 * Transmit a packet (called by the kernel)
 */

//发包函数
int snull_tx(struct sk_buff *skb, struct net_device *dev)
{
 
    int len;
    char *data;
    struct snull_priv *priv = (struct snull_priv *) dev->priv;

    if ( skb == NULL) {
        PDEBUG("tint for %p,  skb %p/n", dev,  skb);
        snull_tx_timeout (dev);
        if (skb == NULL)
            return 0;
    }

    len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;//ETH_ZLEN是所发的最小数据包的长度
    data = skb->data;//将要发送的数据包中数据部分
    dev->trans_start = jiffies; //保存当前的发送时间
    priv->skb = skb;
    snull_hw_tx(data, len, dev);//真正的发送函数
   return 0; /* Our simple device can not fail */
}
/*
 * Deal with a transmit timeout.
 */

//一旦超出watchdog_timeo就会调用snull_tx_timeout
void snull_tx_timeout (struct net_device *dev)
{
   printk("call snull_tx_timeout/n");
    struct snull_priv *priv = (struct snull_priv *) dev->priv;
    PDEBUG("Transmit timeout at %ld, latency %ld/n", jiffies,
                    jiffies - dev->trans_start);
    priv->status = SNULL_TX_INTR;
    snull_interrupt(0, dev, NULL);//超时后发生中断
    priv->stats.tx_errors++;//发送的错误数
    netif_wake_queue(dev); //为了再次发送数据，调用此函数，重新启动发送队列
    return;
}
 
/*
 * Ioctl commands
 */
int snull_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
 
    PDEBUG("ioctl/n");
    return 0;
}
/*
 * Return statistics to the caller
 */
struct net_device_stats *snull_stats(struct net_device *dev)
{
    struct snull_priv *priv = (struct snull_priv *) dev->priv;
    return &priv->stats;//得到统计资料信息
}


//设备初始化函数
int snull_init(struct net_device *dev)
{
   printk("call snull_init/n");

    /*
     * Then, assign other fields in dev, using ether_setup() and some
     * hand assignments
     */
    ether_setup(dev);//填充一些以太网中的设备结构体的项
    dev->open            = snull_open;
    dev->stop            = snull_release;
    //dev->set_config      = snull_config;
    dev->hard_start_xmit = snull_tx;
    dev->do_ioctl        = snull_ioctl;
    dev->get_stats       = snull_stats;
    //dev->change_mtu      = snull_change_mtu;
   // dev->rebuild_header  = snull_rebuild_header;
    //dev->hard_header     = snull_header;

    dev->tx_timeout     = snull_tx_timeout;//超时处理
    dev->watchdog_timeo = timeout;

    /* keep the default flags, just add NOARP */
    dev->flags           |= IFF_NOARP;
    dev->hard_header_cache = NULL;      /* Disable caching */
    SET_MODULE_OWNER(dev);
    /*
     * Then, allocate the priv field. This encloses the statistics
     * and a few private fields.
     */
//为priv分配内存
    dev->priv = kmalloc(sizeof(struct snull_priv), GFP_KERNEL);
  if (dev->priv == NULL)
       return -ENOMEM;
    memset(dev->priv, 0, sizeof(struct snull_priv));
    spin_lock_init(& ((struct snull_priv *) dev->priv)->lock);
    return 0;
}


struct net_device snull_devs[2] = {
    { init: snull_init, },  /* init, nothing more */
    { init: snull_init, }
};

int snull_init_module(void)
{
   int i,result=0;
   strcpy(snull_devs[0].name,"snull0");//net_device结构体中的name表示设备名
   strcpy(snull_devs[1].name,"snull1");//即定义了两个设备，snull0与snull1
    for (i=0; i<2;  i++)
        if ( (result = register_netdev(snull_devs+i)) )//注册设备
            printk("snull: error %i registering device /"%s/"/n",
                   result, snull_devs[i].name);
     return 0;
}
void snull_cleanup(void)
{
    int i;
 
    for (i=0; i<2;  i++) {
        kfree(snull_devs[i].priv);
        unregister_netdev(snull_devs+i);
    }
    return;
}

module_init(snull_init_module);
module_exit(snull_cleanup);
