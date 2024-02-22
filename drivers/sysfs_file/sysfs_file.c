#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>

static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    static int count=0;
    ssize_t size=0;
    
    size=sprintf(buf, "[%d]Hello, world!\n",count++);

    return size;
}

static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    return count; // 这里仅示例，什么也不做，直接返回写入的字节数
}

static struct kobj_attribute my_attribute = __ATTR(my_attr, 0644, my_show, my_store);


static struct attribute *attrs[]={
    &my_attribute.attr,
    NULL,
};


static struct attribute_group attr_group = {
	.attrs = attrs,
};


static struct kobject *my_kobj;

static int mysysfs_init(void)
{
    int retval = 0;
    printk("sysfs init\n");

    my_kobj = kobject_create_and_add("sysfs_file", kernel_kobj);
    if (!my_kobj)
        return -ENOMEM;

    /* Create the files associated with this kobject */
    retval = sysfs_create_group(my_kobj, &attr_group);
    if (retval)
        kobject_put(my_kobj);


    return retval;
}

static void mysysfs_exit(void)
{
    kobject_put(my_kobj);
    printk("sysfs fini, byebye!\n");

}

module_init(mysysfs_init);
module_exit(mysysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LIUGH");



