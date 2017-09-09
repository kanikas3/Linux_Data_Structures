#ifndef MY_RBTREE_H
#define MY_RBTREE_H

	struct mytype *my_search(struct rb_root *root, int n);
	int rb_initial(int);
	int search_rbtree(void);
	int my_insert(struct rb_root *root, struct mytype *data);
	int insert_rbtree(void);	
	int print_rbtree(void);	
	int my_delete(void);
 
	
	

#endif
