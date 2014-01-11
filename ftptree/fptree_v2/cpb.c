#include "list.h"
#include "cpb.h"
#include "fptree.h"


void conditional_parrern_base(struct node *fptree, struct header_table *htable, int *item_index, char *generate_string) {	
	struct frequent_patterns *fp = malloc(sizeof(struct frequent_patterns));
	struct frequent_patterns *fp_head = malloc(sizeof(struct frequent_patterns));
	struct node *now_node = malloc(sizeof(struct node));
	int ptr_index; 
	fp_head = fp;
	fp->next = NULL;
	while(htable != NULL) {		
		if(generate_string != "")
			printf("%s", generate_string);
		
		listStart(htable->cond);		
		while(listNext(htable->cond)) {
			
			now_node = listGet(htable->cond);			
			if(fp->next == NULL && fp->counter != 0) {
				struct frequent_patterns *new_fp = malloc(sizeof(struct frequent_patterns));
				new_fp->ptr  = malloc(sizeof(short) * MIN_SUPPORT_INDEX);
				new_fp->htable_value = htable->no;
				fp->next 	 = new_fp;
				fp 			 = new_fp;
			}
			else if(fp->next != NULL) {
				fp = fp->next;				
			}
			
			fp->counter = now_node->counter;				
			fp->htable_value = htable->no;
			ptr_index   = 0;
			while(now_node->parent != NULL) {			
				*(fp->ptr + ptr_index) = now_node->no;
				ptr_index++;
				now_node = now_node->parent;
			}						
			fp->index = ptr_index;						
		}
		struct header_table *sub_htable = malloc(sizeof(struct header_table));			
		struct node         *sub_tree   = malloc(sizeof(struct node));			
		
		sub_tree = create_sub_fptree();				
		//sub_tree = build_sub_tree(sub_tree, sub_htable, fp_head, htable->no, item_index);
		
		if(sub_tree->child != NULL) {			
			conditional_parrern_base(sub_tree, sub_htable, item_index,  myString_cat(generate_string, htable->no));
		}
		htable = htable->prev;		
	}	
}

struct node *create_sub_fptree() {
	struct node *root = malloc(sizeof(struct node));
	
	root->no      = -1;
	root->parent  = NULL;
	root->counter = 1;
	root->child   = listCreate();
	
	return root;
}


char * myString_cat(char *old_string, int value) {
	short old_length, new_length;
	short i;
	char new_string[4];
	sprintf(new_string, "%d", value);
	old_length = strlen(old_string);
	new_length = strlen(new_string) + 1;
	
	char re_string[old_length + new_length];
	
	strcat(re_string, old_string);
	re_string[old_length] = ',';
	for(i=1;i<new_length;i++) {
		re_string[old_length + i] = new_string[i-1];		
	}	
}

struct node * build_sub_tree(struct node *sub_tree, struct header_table *sub_htable, struct frequent_patterns *fp, short htable_no, int *item_index) {
	struct node *fptree = malloc(sizeof(struct node));
	int i;
	
	
	struct header_table *head = malloc(sizeof(struct header_table));
	create_header_table(sub_htable, head, item_index);
	
	fptree = sub_tree;
	while(fp != NULL) {				
		for(i=0;i< fp->index;i++) {
			if(fp->htable_value == htable_no) {				
				struct node *tmp = malloc(sizeof(struct node));
				
				
				sub_tree = insert_sub_node(sub_tree, *(fp->ptr+i), tmp, sub_htable);
				/*while(sub_htable->no != *(fp->ptr + i))
					sub_htable = sub_htable->next;
				listAdd(sub_htable->cond, sub_tree);				*/
			}
		}
		fp = fp->next;
	}
	
	return fptree;
}

struct node * insert_sub_node(struct node *current_node, short value, struct node *tmp, struct header_table *htable) {		
	if(current_node->child == NULL) {
		list *new_list 	      = listCreate();				
		//current_node->child   = new_list;
		//current_node->no = 100;
		//current_node 		  = link_node(current_node, value);	
		//add_header_table(htable, current_node, value);
		
	}
	else {
		tmp = node_get(current_node->child, value, tmp);
		if(tmp != NULL) {
			current_node 		  = tmp;
			current_node->counter = current_node->counter + 1;
		}
		else {
			current_node = link_node(current_node, value);
			add_header_table(htable, current_node, value);
		}
	}
		
	return current_node;
}
