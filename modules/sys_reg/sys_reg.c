#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/pgtable.h>
#include <asm/desc.h>

#include <linux/seq_file.h>
#include <asm/processor.h>

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef signed short    s16;
typedef int             s32;
typedef unsigned int    u32;
typedef unsigned long long u64;


typedef struct{
   short limit;
   unsigned int address;
}__attribute__((packed)) gdtr_t;

gdtr_t gdtr;

static int sys_reg_show(struct seq_file *m, void *v)
{
    int i;
    u32 cr0;
    u64 *linear_gdt_addr;


    seq_printf(m, "addr: %08x, limit:%d\n", gdtr.address, gdtr.limit);

    asm(" sgdt gdtr");

    seq_printf(m, "addr: %08x, limit:%d\n", gdtr.address, gdtr.limit);

    linear_gdt_addr = (u64*)gdtr.address;
    for(i = 0; i < 32; i++){
        u64 value = *(linear_gdt_addr + i);
        u32 h, l, base, limit;

        h = (u32)(value >> 32);
        l = (u32)(value & 0xFFFFFFFF);

        base = ((h >> 24) & 0xFF) << 24;
        base |= (h & 0xFF) << 16;
        base |= (l >> 16) & 0xFFFF;

        limit = ((h >> 16) & 0xF) << 16;
        limit |= l & 0xFFFF;



        seq_printf(m, "%2d: %016llx  base:%08x  limit:%d\n", i, *(linear_gdt_addr + i), base, limit);
    }




    cr0 = read_cr0();
    seq_printf(m, "cr0 = %08x\n", cr0);

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






