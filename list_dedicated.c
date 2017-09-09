#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/random.h>

	/*declaration*/
	static struct my_list2 {
		struct list_head test_list2;
		int temp2;
	};
	
	static int dstruct_size;
	struct list_head test_head2;
	struct list_head *ptr2;
	
//initial function
int lld_initial(int _dstruct_size){
	dstruct_size=_dstruct_size;
	INIT_LIST_HEAD(&test_head2);
	return 0;
}

//create list function
int create_mylist(void){
	
	int i=0;
	for(;i<dstruct_size;i++){
		struct my_list2 *new_entry;
		new_entry=kmalloc(sizeof(struct my_list2 *),GFP_KERNEL);
		if(new_entry == NULL){
			printk("ENOMEM - out of memory\n");
		}
		get_random_bytes(&new_entry->temp2,4);
		list_add(&new_entry->test_list2,&test_head2);
	}	
	return 0;
}

//print list function
int print_mylist(void){

	struct my_list2 *entry;
	struct list_head *ptr;
	list_for_each(ptr, &test_head2){
		entry = list_entry(ptr, struct my_list2, test_list2);
		printk(KERN_INFO "The value inserted in dedicated linked list is %d \n", entry->temp2);
	
	}
	return 0;	
}

//delete list function
int del_mylist(void){
	
	struct my_list2 *temp2;
	struct my_list2 *entry;
	list_for_each_entry_safe(entry, temp2, &test_head2, test_list2){
		list_del(&(entry->test_list2));
		kfree(entry);
	}
	printk(KERN_INFO "\n %d \n",list_empty(&test_head2));

	return 0;

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanika Sabharwal <kanikas3@vt.edu");
MODULE_DESCRIPTION("Data Structure Kernel Module");

