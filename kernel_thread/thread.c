#include <linux/delay.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>

static struct stask_struct *test_task_struct;

int thread_task(void *arg)
{
	static int count = 0;
    static int topn_timer = 0;
	while(1){
		if(kthread_should_stop()){
			printk("thread task: kthread_should_stop\n");
			break;
		}

		set_current_state(TASK_INTERRUPTIBLE);

		//schedule_timeout(5);
		ssleep(1);

		if(++topn_timer >=10){
			printk("thread task: count=%d\n",++count);
			topn_timer=0;
        }

	}

	return 0;
}


static int __init init_kernel_thread(void)
{
	test_task_struct = kthread_create(thread_task, NULL, "Kernel Thread");
    if(IS_ERR(test_task_struct)){
		printk("kthread_create error\n");
	}else{
		wake_up_process(test_task_struct);
	}
	return 0;
}


static void __exit exit_kernel_thread(void)
{
	kthread_stop(test_task_struct);
}

module_init(init_kernel_thread);
module_exit(exit_kernel_thread);












