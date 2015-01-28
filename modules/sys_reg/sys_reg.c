 #include <linux/module.h>    
 #include <linux/proc_fs.h>    
 #include <linux/sched.h>
 #include <asm/uaccess.h>
 #include <asm/desc.h>
 #include <asm/pgtable.h>
 #include <asm/desc.h>



 int init_module( void )
 {
	return	0;  
 }


 void cleanup_module( void )
 {

 }

 MODULE_LICENSE("GPL");

