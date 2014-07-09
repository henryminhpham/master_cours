#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_DESCRIPTION("Module \"hello word param\" pour noyau 2.6");
MODULE_AUTHOR("Olivier Pitton");
MODULE_LICENSE("GPL");

static char* whom;
static int howmany;
module_param(whom, charp,  S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(whom, "A firstname");

module_param(howmany, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(howmany, "An integer");

static int hello_init(void)
{
  int i;
  for(i = 0 ; i < howmany ; i++)
    printk(KERN_ALERT "Hello, %s\n", whom);
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_ALERT "Goodbye, %s\n", whom);
}

module_init(hello_init);

module_exit(hello_exit);

