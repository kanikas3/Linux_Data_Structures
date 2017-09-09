#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/random.h>
#include "list_common.h"
#include "list_dedicated.h"
#include "my_queue.h"
#include "my_rbtree.h"
#include "my_map.h"

	static int dstruct_size = 10;
	module_param(dstruct_size,int,0);

/*init module*/
static int __init create_list_init(void){ 
	
	//LINKED LIST WITH ONE COMMON FUNCTION
	llc_initial(dstruct_size);	
	int result=common_func();
	printk(KERN_INFO "perfomed functions of linked list with common function successfully with return value %d\n",result);
	

	//LINKED LIST WITH DEDICATED FUNCTION
	lld_initial(dstruct_size);
	int result1=create_mylist();
	int result2=print_mylist();
	int result3=del_mylist();
	printk(KERN_INFO "The linked list operation of create, print and delete are exclusively and successfully performed with value returned as %d, %d and %d\n",result1,result2,result3);
	
	//QUEUE
	//queue implementation
	q_initial(dstruct_size);
	int result4=testfunc();
	printk(KERN_INFO "Queue operations performed successfully with return value of %d\n",result4);
	
	//RB TREE
	//insert data in rbtree
	rb_initial(dstruct_size);
	int rb_res1 = insert_rbtree();
	printk(KERN_INFO "insertion in tree complete value returned %d\n",rb_res1);

	//printing data
	int rb_res2 = print_rbtree();
	printk(KERN_INFO "printing of tree complete value returned %d\n", rb_res2);

	//searching and deleting data
	int rb_res3 = search_rbtree();
	printk(KERN_INFO "search and delete of tree complete value returned is %d\n",rb_res3);
	//printing data again
	int rb_res4 = print_rbtree();
	printk(KERN_INFO "print once more the tree complete value returned is %d\n",rb_res4);
	
	//destoy tree
	int rb_res5=my_delete();
	printk(KERN_INFO "RB Tree is destoyed and value returned is %d\n",rb_res5);
	
	//MAP 
	//map alloc id
	id_initial(dstruct_size);
	int id_res1 = id_alloc();
	if(id_res1==-1){
		//ENOSPC
		printk(KERN_INFO "No space on the drive\n");
	}else if(id_res1 == -2){
		//ENOMEM
		printk(KERN_INFO "Insufficient memory\n");
	}else{
		printk(KERN_INFO "id is alloc and value returned is %d\n",id_res1);
	}
		//map print id
	int id_res2 = id_lookup();
	printk(KERN_INFO "map is printed and value returned is %d\n",id_res2);

	//map delete
	int id_res3 = id_delete();
	printk(KERN_INFO "map is deletd and value returned is %d\n",id_res3);
		
	
	printk(KERN_INFO "The value returned for common func is %d \n",result);
	printk(KERN_INFO "The value returned from dedicated func is %d, %d and %d \n", result1, result2,  result3);
	//printk(KERN_INFO "queue enq deq is %d \n",result4);
	return 0;
}


/*exit module*/
static int __exit create_list_exit(void){
		return 0;
}


module_init(create_list_init);
module_exit(create_list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanika Sabharwal <kanikas3@vt.edu");
MODULE_DESCRIPTION("Data Structure Kernel Module");

