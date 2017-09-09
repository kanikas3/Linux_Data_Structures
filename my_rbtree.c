#include <linux/rbtree.h>
#include <linux/random.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include "my_rbtree.h"

//initializing
static struct mytype{
	struct rb_node node;
	int id;
};
static int dstruct_size;
struct rb_root mytree = RB_ROOT;

//init function
int rb_initial(int _dstruct_size){
	
	dstruct_size=_dstruct_size;
	return 0;
}

//search
struct mytype *my_search(struct rb_root *root, int n)
{
	struct rb_node *node = root->rb_node;
	while(node){
		struct mytype *data = container_of(node, struct mytype, node);
		//struct mytype *this = container_of(*new, struct mytype, node);
		
		if(data->id<n){
			node = node->rb_left;
		}else if(data->id>n){
			node = node->rb_right;
		}else{
			return data;
		}
		return NULL;	

		/*
		int result;
		result = strcmp(n,data->id);

		if(result<0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
		}
		return NULL;
		*/
}
}

//insertion
int my_insert(struct rb_root *root, struct mytype *data)
{
	struct rb_node **new = &(root->rb_node),*parent=NULL;

	/*location of insertion*/
	while(*new){
		struct mytype *this = container_of(*new, struct mytype, node);
		int result = 0;
		if(data->id<this->id){
			result=-1;
		}else if(data->id>this->id){
			result= 1;
		}	

		parent = *new;
		if(result<0)
			new = &((*new)->rb_left);
		else if (result>0)
			new = &((*new)->rb_right);
		else	
			return -1;
	}
	/*add node and balance tree*/
	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node,root);
	return 0;
}



//search and delete implementation
int search_rbtree(void){
	int i=0;
	for(;i<100;i++){
		struct mytype *data = my_search(&mytree,i);
		if(data!=NULL){
			//element present so remove
			printk(KERN_INFO "element %d is present and shall now be deleted\n",i);
			rb_erase(&data->node, &mytree);
			kfree(data);
			
		}else{
			printk(KERN_INFO "element %d is not present\n",i);
		}
	}
	return 0;
}


//insertion implementation
int insert_rbtree(void){
	
	int i=0;
	struct mytype *data;
	int n;
	for(;i<dstruct_size;){
		char c;

		get_random_bytes(&c,1);
		n=(int)c;
		data=kmalloc(sizeof(struct mydata *), GFP_KERNEL);
	 	if(data == NULL){
			printk("ENOMEM - out of memory\n");
		}
		data->id = n;
		int result = my_insert(&mytree, data);
		if(result == -1){
			i++;
		}
	}
	return 0;
}

//printing tree
int print_rbtree(void){
	struct rb_node *node;
	for(node=rb_first(&mytree);node;node=rb_next(node))
		printk("The tree has key=%d\n",rb_entry(node,struct mytype, node)->id);
return 0;

}

//deleting
int my_delete(void) 
{
	struct mytype *entry, *temp;
	
	rbtree_postorder_for_each_entry_safe(entry, temp, &mytree, node)
	{
		rb_erase(&entry->node, &mytree);
	}
	
return 0;
}


