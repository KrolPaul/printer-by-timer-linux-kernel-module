/*
 * Module for linux kernel 5.10.
 *
 * Description:
 * Module writes line:
 *	Hello from kernel module
 * to chosen file by timer.
 */

#include <linux/init.h> /* необходим для макросов*/
#include <linux/kernel.h> /* необходим для pr_info() */
#include <linux/module.h> /* необходим для всех модулей */
#include <linux/timer.h>
#include <linux/jiffies.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Krol");
MODULE_DESCRIPTION("Module prints <Hello from kernel module> to file every N seconds");

/* Module params */
static int print_every_n_sec = 10; 
module_param(print_every_n_sec, int, 0);
static char * file_name = "default-print-fn";
module_param(file_name, charp, 0);

static struct timer_list printer_timer;

static void printer_helper(void)
{
	char printer_prog[] = "/home/paul/module/user-space/printer";
	char *arg[] = {printer_prog, "kuku", "Hey", NULL};
	char *env[] = {NULL};
	int ret = call_usermodehelper(printer_prog, arg, env, UMH_WAIT_PROC);
	pr_info("Return code? %i", ret);
	
}

static void timer_start(struct timer_list * timer)
{
	int ret = mod_timer(
		timer,
		jiffies + msecs_to_jiffies(print_every_n_sec * MSEC_PER_SEC)
	);
	if (ret)
		pr_info("Error while starting timer\n");
}

static void timer_callback(struct timer_list * timer)
{
	pr_info("Interrupt works!");
	//printer_helper();
	timer_start(timer);
}


static int __init init(void)
{
    pr_info("Module init!\n");
	//pr_info("File name: %s\n", file_name);
	//pr_info("Write every N seconds: %d\n", print_every_n_sec);
	
	timer_setup(&printer_timer, timer_callback, 0);
	timer_start(&printer_timer);

    return 0;
}
 
static void __exit cleanup(void)
{
	timer_delete(&printer_timer);
}

module_init(init)
module_exit(cleanup)
