#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
    printk("hello world!\n");

    return 0;
}

static void hello_exit(void)
{
    printk("byebye!\n");

}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LIUGH");



