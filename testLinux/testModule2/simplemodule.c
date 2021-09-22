#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_AUTHOR("Washington Ruan");
MODULE_DESCRIPTION("A very simple loadable module that does almost nothing.");

int int_simple(void)
{
    printk("in init module simple\n");
    return 0;
}

void cleanup_simple(void)
{
    printk("in cleanup module simple\n");
}

module_init(int_simple);
module_exit(cleanup_simple);
MODULE_LICENSE("GPL");