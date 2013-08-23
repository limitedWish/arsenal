#include <linux/init.h>
#include <linux/module.h>

#include "procfs.h"

MODULE_LICENSE("Dual BSD/GPL");

static int __init
memhack_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    proc_init();
    return 0;
}

static void __exit
memhack_exit(void)
{
    proc_fini();
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(memhack_init);
module_exit(memhack_exit);
