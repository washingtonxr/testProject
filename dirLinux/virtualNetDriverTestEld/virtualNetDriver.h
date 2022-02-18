#ifndef _VIRTUALNETDRIVER_H_
#define _VIRTUALNETDRIVER_H_

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


int virtualNetOpen(struct net_device *dev);
int virtualNetRelease(struct net_device *dev);
void virtualNetRx(struct net_device *dev, int len, unsigned char *buf);
void virtualNetInterrupt(int irq, void *dev_id, struct pt_regs *regs);
void virtualNetHwTx(char *buf, int len, struct net_device *dev);
int virtualNetTx(struct sk_buff *skb, struct net_device *dev);
void virtualNetTxTimeout (struct net_device *dev);
int virtualNetIoctl(struct net_device *dev, struct ifreq *rq, int cmd);
struct net_device_stats *virtualNetStats(struct net_device *dev);
int virtualNetInit(struct net_device *dev);
int virtualNetInitModule(void);
void virtualNetCleanup(void);

#endif
