/*
 * Module for linux kernel 5.10.
 *
 * Description:
 * Module writes line:
 *	Hello from kernel module
 * to chosen file by timer.
 */

#include <linux/init.h>
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/timer.h>
#include <linux/jiffies.h>

#define perror(str, err) pr_err(str ": %pe\n", ERR_PTR(err))
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Krol");
MODULE_DESCRIPTION("Module prints <Hello from kernel module> to file every N seconds");


/* Module params */
static int print_every_n_sec = 10; 
module_param(print_every_n_sec, int, 0);
static char * file_name = MODULE_DIR "printer-module-temp";
module_param(file_name, charp, 0);


struct work_struct timer_isr_bottom;
static struct timer_list printer_timer;

static void print(struct work_struct * work)
{
	static char* print_text = "Hello from kernel module";
	static char* print_prog_path = MODULE_DIR "helper/printer";
	
	char *argv[] = {print_prog_path, file_name, print_text, NULL};
	static char *env[] = {NULL};
	
	int err = call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
	if (err)
		perror("Error while calling helper (printer)", err);
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
	schedule_work(&timer_isr_bottom);
	timer_start(timer);
}


static int __init startup(void)
{
	if (print_every_n_sec < 1){
		pr_err("Module loading failed! Print interval must be > 0");
		return -1;
	}
	
	timer_setup(&printer_timer, timer_isr_top, 0);
	timer_start(&printer_timer);
	
	pr_info("Module loaded!");
	pr_info("Print to file: %s\n", file_name);
	pr_info("Every N seconds: %d\n", print_every_n_sec);
    return 0;
}
 
static void __exit cleanup(void)
{
	del_timer(&printer_timer);
	flush_scheduled_work();
	pr_info("Module unloaded!");
}

module_init(startup)
module_exit(cleanup)

#undef perror
