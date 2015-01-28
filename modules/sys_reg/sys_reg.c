#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/pgtable.h>
#include <asm/desc.h>
#include <linux/seq_file.h>

static int sys_reg_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello proc from zi \n");

    return 0;
}

static int sys_reg_open(struct inode *inode, struct file *file)
{
    return single_open(file, sys_reg_show, NULL);
}



static const struct file_operations sys_reg_fops =
{
    .owner      = THIS_MODULE,
    .open       = sys_reg_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};


static int __init sys_reg_init(void) {
    proc_create("sys_reg", 0, NULL, &sys_reg_fops);
    return 0;
}

static void __exit sys_reg_exit(void) {
    remove_proc_entry("sys_reg", NULL);
}


MODULE_LICENSE("GPL");
module_init(sys_reg_init)
module_exit(sys_reg_exit)






