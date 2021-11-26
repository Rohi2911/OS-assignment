#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gfp.h>

SYSCALL_DEFINE1(my_precious, void *, kaddress) 
{
	struct task_struct *p = current;
	struct vm_area_struct *q = p->mm->mmap;
	struct vm_area_struct *vm_pointer = q;
	
	while(!vma_is_anonymous(vm_pointer))
		vm_pointer = vm_pointer->vm_next;
	
	unsigned long size = vm_pointer->vm_end - vm_pointer->vm_start;
	kaddress = kmalloc(size, GFP_USER);	
	unsigned long a = copy_from_user(kaddress, vm_pointer->vm_start, size);
	if(a == 0) {
		printk("System call executed successfully\n");
		return 0;
		}
	else
		return -1;
}
