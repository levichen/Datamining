#include "fptree.h"

struct node * create_fptree() {
	struct node *root = malloc(sizeof(struct node));
	hashmap *myHash = hashmapCreate(0);
	
	root->no      = -1;
	root->parent  = NULL;
	root->counter = 1;
	root->child   = myHash;
	
	return root;
}

void build_fptree(struct node *fptree, int *mItem, int *item_index, int *mPow) {
	int item_count = 66;
	int i, j, transcation_counter, value;
	int index, bit_index;
	
	struct node *root = malloc(sizeof(struct node));
	struct node *tmp  = malloc(sizeof(struct node));
	root = fptree;
	
	for(i=0;i < TRANSCATION_COUNT;i++) {		
		transcation_counter = i * SIZE_OF_ARRAY;		
		for(j=0;j<item_count;j++) {						
			value 	  = *(item_index + j);			
			index     = value / 31 + transcation_counter;			
			bit_index = value % 31;
			
			if(value == 0) bit_index = 1;
			else bit_index++;			
			
			if(*(mItem + index) & mPow[bit_index]) {				
				fptree = insert_node(fptree, value, tmp);									
			}			
		}
		fptree = root;
	}			
	free(mItem);
	free(item_index);
}

struct node * insert_node(struct node *current_node, short value, struct node *tmp) {
	tmp = hashmapGet(current_node->child, value);	
	if(tmp != NULL) {		
		current_node 		  = tmp;
		current_node->counter = current_node->counter + 1;
	}
	else {
		struct node *new_node = malloc(sizeof(struct node));
		hashmap *new_hash 	  = hashmapCreate(0);
		
		new_node->no 	  = value;
		new_node->parent  = current_node;
		new_node->counter = 1;
		new_node->child	  = new_hash;
		
		hashmapInsert(current_node->child, new_node, value);
		current_node = new_node;		
	}
	return current_node;
}
