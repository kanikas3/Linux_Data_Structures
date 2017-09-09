#include <linux/init.h>
#include <linux/module.h>
#include <linux/idr.h>
#include <linux/random.h>
#include <linux/errno.h>
#include <linux/slab.h>

//initializing
static struct idr my_map;
static int dstruct_size;

//init function
int id_initial(int _dstruct_size){
	idr_init(&my_map);
	dstruct_size = _dstruct_size;
	return 0;
}

//ID allocation function
int id_alloc(void){
	int i=0;
	int id;
	int* n;
	char c;
	for(;i<dstruct_size;i++){
		get_random_bytes(&c,1);
		n=kmalloc(sizeof(int),GFP_KERNEL);
		if(n == NULL){
			printk("ENOMEM - out of memory\n");
		}
		*n=(int) c;
		idr_preload(GFP_KERNEL);
		id=idr_alloc(&my_map, n, 1, 500, GFP_KERNEL);
		idr_preload_end();
		if(id== -ENOSPC)
			return -1;
		else if(id == -ENOMEM)
			return -2;	
	}
	return 0;
}

//looking up ID and printing
int id_lookup(void){
	int i=0;
	for(;i<500;i++){
		int *data = idr_find(&my_map,i);
		if(data){
			printk(KERN_INFO "id: %d has the value:%d \n",i,*data);
		}
	}
	return 0;
}

//deleting map
int id_delete(void){
	int i=0;
	for(;i<500;i++){
		struct mytype *data = idr_find(&my_map,i);
		if(data){
			idr_remove(&my_map,i);
		}
	}
	return 0;
}

