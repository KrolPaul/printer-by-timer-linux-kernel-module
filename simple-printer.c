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

#define perror(str, err) pr_err(str ": %pe\n", ERR_PTR(err))
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Krol");
MODULE_DESCRIPTION("Module prints <Hello from kernel module> to file every N seconds");


/* Module params */
static int print_every_n_sec = 5; 
module_param(print_every_n_sec, int, 0);
static char * file_name = "/home/paul/module/user-space/heythere";
module_param(file_name, charp, 0);


struct work_struct timer_isr_bottom;
static struct timer_list printer_timer;


static void print(struct work_struct * work)
{
	static char* print_prog = "/home/paul/module/user-space/printer";
	static char* print_text = "Hello from kernel module";
	
	char *argv[] = {print_prog, file_name, print_text, NULL};
	static char *env[] = {NULL};
	
	int err = call_usermodehelper(print_prog, argv, env, UMH_WAIT_PROC);
	if (err)
		perror("Error while calling user space printer", err);
}

DECLARE_WORK(timer_isr_bottom, print);

static void timer_start(struct timer_list * timer)
{
	int err = mod_timer(
		timer,
		jiffies + msecs_to_jiffies(print_every_n_sec * MSEC_PER_SEC)
	);
	if (err)
		perror("Error while starting timer", err);
}

static void timer_isr_top(struct timer_list * timer)
{
	pr_info("Interrupt works!");
	schedule_work(&timer_isr_bottom);
	timer_start(timer);
}


static int __init startup(void)
{
    pr_info("Module startup!\n");
	//pr_info("File name: %s\n", file_name);
	//pr_info("Write every N seconds: %d\n", print_every_n_sec);
	
	timer_setup(&printer_timer, timer_isr_top, 0);
	timer_start(&printer_timer);

    return 0;
}
 
static void __exit cleanup(void)
{
	pr_info("Module cleanup!");
	del_timer(&printer_timer);
}

module_init(startup)
module_exit(cleanup)

#undef perror
