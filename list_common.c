#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/random.h>

	static int dstruct_size;
	static struct my_list {
		struct list_head test_list;
		int temp;
	};

	static struct list_head test_head;
	static struct list_head *ptr;


//initial function
int llc_initial(int _dstruct_size){
	dstruct_size = _dstruct_size;
	INIT_LIST_HEAD(&test_head);
	return 0;
}

//action function
int common_func(void){
	
	/*creating a list*/
	int i=0;
	char c;
	for(;i<dstruct_size;i++){
		struct my_list *new_entry;
		new_entry=kmalloc(sizeof(struct my_list *),GFP_KERNEL);
		get_random_bytes(&new_entry->temp,4);
		list_add(&new_entry->test_list,&test_head);
	}		

	/*printing the list*/
	struct my_list *entry;
	list_for_each(ptr, &test_head){
		entry = list_entry(ptr, struct my_list, test_list);
		printk(KERN_INFO "The value entered in linked list is %d \n", entry->temp);
	}	

	/*delete the list*/
	struct my_list *temp;
	list_for_each_entry_safe(entry, temp, &test_head, test_list){
		list_del(&(entry->test_list));
		kfree(entry);
	}
	printk(KERN_INFO "\n %d \n",list_empty(&test_head));

	return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kanika Sabharwal <kanikas3@vt.edu");
MODULE_DESCRIPTION("Data Structure Kernel Module");

