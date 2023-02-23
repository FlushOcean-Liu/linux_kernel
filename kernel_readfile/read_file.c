#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static struct file *fp;


/* 读取每一行，一换行符为标志，记录读取位置 */
static char *read_line(char *buf, int buf_len, struct file *fp)
{
    int ret;
    int i=0;
    mm_segment_t fs;
	
    fs=get_fs();
    set_fs(KERNEL_DS);
    ret = fp->f_op->read(fp, buf, buf_len, &(fp->f_pos));
    set_fs(fs);

    if(ret<=0)
        return NULL;

    while(buf[i++]!='\n' && i< ret);

    if(i<ret){// fp->f_pos置为换行符位置
        fp->f_pos +=i-ret;
    }

    if(i<buf_len){
        buf[i-1]=0;
    }

    return buf;
}


static int __init init()
{
    printk("%s()\n", __FUNCTION__);
    /*
        filp_open()是一个异步执行函数。它会异步打开指定的文件。
        如果打开了文件后面没干其它事直接就结束这个函数，那么就很有可能出现后面的打印不显示的现象。
    */
    fp = filp_open("./test.txt", O_RDONLY, 0); //参数3的文件模式对于读文件而言作用不大。
    printk("fs file address:0x%p\n", fp);
    msleep(100);
    if(IS_ERR(fp))//要用这个 IS_ERR() 来检查指针是否有效，而不能直接判断指针是否为NULL。
    {
        printk("cannot open fs.\n");
        goto FS_END;
    }

    mm_segment_t old_fs;
    old_fs = get_fs();
    set_fs(KERNEL_DS);

    int size = 0;
    char rbuf[256];
    loff_t pos = 0;
    char *tmp=NULL;
    while(1)
    {
        memset(rbuf, 0, 256);
        /*
            参数2要求是 __user 空间的内存地址，
            如果要直接使用内核中创建的数组，
            则在使用之前应先将文件系统状态切换到 KERNEL_DS 态。即上面的 set_fs(KERNEL_DS) 调用。

            参数3是读取指针的位置，对于普通文件而言，它必须传入一个有效的 loff_t 指针以实现“断点续读”的功能。
        */
 #if 0
        size = vfs_read(fp, rbuf, 12, &pos);
        printk("read ret:%d, pos:%ld\n", size, pos);
        if(size < 1)
        {
            printk("read end.\n");
            break;
        }
#endif
        tmp=read_line(rbuf, 256, fp);
        if(tmp)
            printk("%s\n", rbuf);
	else 
	    break;
    }
    set_fs(old_fs);
    
    msleep(50);
FS_END:
    
    return 0;
}

static void __exit exit()
{
    if(!IS_ERR(fp))
    {
        printk("closing fs file.\n");
        int ret = filp_close(fp, NULL);
        printk("close ret:%d\n", ret);
    }

    msleep(100);
}

module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");
