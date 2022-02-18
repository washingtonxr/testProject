#include <net/netlink.h>
#include <net/genetlink.h>
#include <linux/version.h>
 
 
#define TEST_GENL_FAMILY_NAME "my-test-family"
#define TEST_GENL_MCAST_GROUP_NAME "my-test-group"
#define TEST_GENL_MSG_FROM_KERNEL   "Hello from kernel space!!!"
 
/* handler
 * message handling code goes here; return 0 on success, negative
 * values on failure
 */
static int doc_exmpl_echo(struct sk_buff *skb, struct genl_info *info);
 
 
 
/* netlink attributes 可以通过枚举索引找到对应的类型，用户空间应用程序要传递这样的信息 */
enum {
      DOC_EXMPL_A_UNSPEC,
      DOC_EXMPL_A_MSG,
      __DOC_EXMPL_A_MAX,
};
#define DOC_EXMPL_A_MAX (__DOC_EXMPL_A_MAX - 1)
 
/* attribute policy */
static struct nla_policy doc_exmpl_genl_policy[DOC_EXMPL_A_MAX + 1] = {
      [DOC_EXMPL_A_MSG] = { .type = NLA_NUL_STRING },
};
 
/* commands 定义命令类型，用户空间以此来表明需要执行的命令 */
enum {
    DOC_EXMPL_C_UNSPEC,
    DOC_EXMPL_C_ECHO,
    __DOC_EXMPL_C_MAX,
};
#define DOC_EXMPL_C_MAX (__DOC_EXMPL_C_MAX - 1)
 
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,13,0)
 
/* family definition */
static struct genl_family doc_exmpl_genl_family = {
      .id = GENL_ID_GENERATE,   //request a new channel number, assigned by kernel, NOT driver specific
      .hdrsize = 0,
      .name = "DOC_EXMPL",
      .version = 1,
      .maxattr = DOC_EXMPL_A_MAX,
};
 
/* operation definition 将命令command echo和具体的handler对应起来 */
static struct genl_ops doc_exmpl_genl_ops_echo = {
        .cmd = DOC_EXMPL_C_ECHO,
        .flags = 0,
        .policy = doc_exmpl_genl_policy,
        .doit = doc_exmpl_echo,
        .dumpit = NULL,
};
 
static struct genl_multicast_group doc_exmpl_genl_mcgrp = {
        .name = "DOC_EXMPL_GRP",
};
 
//需要在其他地方主动调用这个函数发送广播
static int test_netlink_send(void)
{
    struct sk_buff *skb = NULL;
    void *msg_header = NULL;
    int size;
    int rc;
 
    /* allocate memory */
    size = nla_total_size(strlen(TEST_GENL_MSG_FROM_KERNEL) + 1) + nla_total_size(0);
 
    skb = genlmsg_new(size, GFP_KERNEL);
    if (!skb)
        return -ENOMEM;
 
    /* add the genetlink message header */
    msg_header = genlmsg_put(skb, 0, 0,
                            &doc_exmpl_genl_family, 0, DOC_EXMPL_C_ECHO);
    if (!msg_header)
    {
        rc = -ENOMEM;
        goto err_out;
    }
 
    /* add a DOC_EXMPL_A_MSG attribute */
    rc = nla_put_string(skb, DOC_EXMPL_A_MSG, TEST_GENL_MSG_FROM_KERNEL);
    if (rc != 0)
        goto err_out;
 
    /* finalize the message */
    genlmsg_end(skb, msg_header);
 
    //multicast is send a message to a logical group
    rc = genlmsg_multicast(skb, 0, doc_exmpl_genl_mcgrp.id, GFP_KERNEL);
    if (rc != 0 && rc != -ESRCH)
    {
        /* if NO one is waitting the message in user space,
         * genlmsg_multicast return -ESRCH
         */
        LOGC("genlmsg_multicast to user failed, return %d", rc);
 
        /*
         * attention:
         * If you NOT call genlmsg_unicast/genlmsg_multicast and error occurs,
         * call nlmsg_free(skb).
         * But if you call genlmsg_unicast/genlmsg_multicast, NO need to call
         * nlmsg_free(skb). If NOT, kernel crash.
         */
        return rc;
    }
 
    LOGC("genlmsg_multicast Success");
 
    /*
     * Attention:
     * Should NOT call nlmsg_free(skb) here. If NOT, kernel crash!!!
     */
    return 0;
 
err_out:
    if (skb)
        nlmsg_free(skb);
    return rc;
}
 
 
static int genetlink_init(struct my_module_priv *ctx)
{
    int rc;
 
    /**
     * 1. Registering A Family
     * This function doesn't exist past linux 3.12
     */
    rc = genl_register_family(&doc_exmpl_genl_family);
    if (rc != 0)
        goto err_out1;
 
    rc = genl_register_ops(&doc_exmpl_genl_family, &doc_exmpl_genl_ops_echo);
    if (rc != 0)
        goto err_out2;
 
    /*
     * for multicast
     */
    rc = genl_register_mc_group(&doc_exmpl_genl_family, &doc_exmpl_genl_mcgrp);
    if (rc != 0)
        goto err_out3;
 
    LOGC("doc_exmpl_genl_mcgrp.id=%d", doc_exmpl_genl_mcgrp.id);
    LOGC("genetlink_init OK");
    return 0;
 
err_out3:
    genl_unregister_ops(&doc_exmpl_genl_family, &doc_exmpl_genl_ops_echo);
err_out2:
    genl_unregister_family(&doc_exmpl_genl_family);
err_out1:
    LOGC("Error occured while inserting generic netlink example module\n");
    return rc;
}
 
static void genetlink_exit(struct my_module_priv *ctx)
{
    LOGC("Generic Netlink Example Module unloaded.");
 
    genl_unregister_mc_group(&doc_exmpl_genl_family, &doc_exmpl_genl_mcgrp);
    genl_unregister_ops(&doc_exmpl_genl_family, &doc_exmpl_genl_ops_echo);
    genl_unregister_family(&doc_exmpl_genl_family);
}
 
static struct my_module_work g_my_module_work = {
        .do_test_probe = genetlink_init,
        .do_test_remove = genetlink_exit,
};