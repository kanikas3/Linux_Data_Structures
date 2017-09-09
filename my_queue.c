#include <linux/init.h>
#include <linux/module.h>
#include <linux/kfifo.h>
#include <linux/errno.h>
#include <linux/random.h>
#include <linux/slab.h>

#define FIFO_SIZE 32
#define DYNAMIC
#ifdef DYNAMIC
static DECLARE_KFIFO_PTR(test,int);
#else
static DECLARE_KFIFO(test,int,FIFO_SIZE);
#endif

static int dstruct_size;

//init function
int q_initial(int _dstruct_size){
	dstruct_size=_dstruct_size;
	return 0;
}

//action function
int testfunc(void)
{
	int i;
	int buf[6];
	unsigned int ret;	
	unsigned int copied;

#ifdef DYNAMIC
	if(kfifo_alloc(&test,dstruct_size*4,0)){
		printk("error kfifo_alloc\n");
		return 1;
	}
#else
	INIT_KFIFO(test);
#endif
	printk("fifo test has started\n");
	
	if(kfifo_initialized(&test))
		printk("fifo initialized\n");

	//enqueue
	int* n;
	char c;
	for(i=0;i<dstruct_size;i++){
		get_random_bytes(&c,1);
		n=kmalloc(sizeof(int),GFP_KERNEL);
		if(n == NULL){
			printk("ENOMEM - out of memory\n");
		}
		*n = (int)c;
		kfifo_in(&test,n,sizeof(int));
		printk("enqueued the value of %d\n",*n);
	}

	//dequeue
	n=kmalloc(sizeof(int),GFP_KERNEL);
	while(!kfifo_is_empty(&test)){
		
		
		kfifo_out(&test,n,sizeof(int));
		printk("the value is %d dequed\n",*n);

	}
	printk("dequeue over\n");
	return 0;
}
