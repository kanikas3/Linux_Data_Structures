obj-m := hw2.o	
hw2-objs := my_main.o my_queue.o list_common.o list_dedicated.o my_rbtree.o my_map.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: my_main.c list_common.c list_dedicated.c my_queue.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean 	
