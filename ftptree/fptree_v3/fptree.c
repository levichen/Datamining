#include "fptree.h"

struct node 		     *tree_root;
struct node 			 *node_tmp;
struct header_table 	 *header_head;
struct frequent_patterns *fp_head;

void init() {
	tree_root   = malloc(sizeof(struct node));
	node_tmp    = malloc(sizeof(struct node));
	header_head = malloc(sizeof(struct header_table));
	fp_head     = malloc(sizeof(struct frequent_patterns));
}


//初始化樹的根結點
struct node * create_fptree() {
	struct node *root = malloc(sizeof(struct node));
	
	root->no      = -1;
	root->parent  = NULL;
	root->counter = 1;
	root->child   = NULL;
	
	return root;
}

//建造樹的內容
void build_fptree(struct node *fptree, int *mItem, int *item_index, struct header_table *htable) {	
	int i, j, transcation_counter, value;
	int index, bit_index;
	
	htable      = create_header_table(htable, item_index);
	tree_root   = fptree;	
	header_head = htable;
	
	for(i=0;i < TRANSCATION_COUNT;i++) {				
		transcation_counter = i * SIZE_OF_ARRAY;		
		for(j=0;j<MIN_SUPPORT_INDEX;j++) {						
			value 	  = *(item_index + j);			
			index     = value / 31 + transcation_counter;			
			bit_index = value % 31;
			
			bit_index++;
			if(value == 0) bit_index = 1;			
			
			if((*(mItem + index) >> (bit_index-1)) & 1) {				
				fptree = insert_node(fptree, value, htable, 1);										
			}			
		}
		fptree = tree_root;				
		htable = header_head;
	}		
	//htable = head;
	free(mItem);
	//free(item_index);
}

//插入樹結點
struct node * insert_node(struct node *current_node, short value, struct header_table *htable, int counter) {		
	if(current_node->child == NULL) {
		//list *new_list 	      = listCreate(0);		
		current_node->child   = listCreate();
		current_node 		  = link_node(current_node, value);	
		add_header_table(htable, current_node, value);
		current_node->counter = counter;
	}
	else {
		node_tmp = node_get(current_node->child, value, node_tmp);
		if(node_tmp != NULL) {
			current_node 		  = node_tmp;
			current_node->counter = current_node->counter + 1;
		}
		else {
			current_node = link_node(current_node, value);
			add_header_table(htable, current_node, value);
			current_node->counter = counter;
		}
	}
		
	return current_node;
}

//將兩結點串連
struct node * link_node(struct node *current_node, short value) {
	struct node *new_node = malloc(sizeof(struct node));	
	
	new_node->no 	  = value;
	new_node->parent  = current_node;
	new_node->counter = 1;
	new_node->child	  = NULL;
	
	listAdd(current_node->child, new_node);
	current_node = new_node;
	return current_node;
}

//取得子結點
void* node_get(list *mList, short value, struct node *tmp) {	
	listStart(mList);
	while(listNext(mList)) {
		tmp = listGet(mList);
		if(tmp->no == value)
			return tmp;
	}
	return NULL;
}

//深度優先搜尋法
void dfs(struct node *root) {
	struct node *current = malloc(sizeof(struct node));
	
	current = root;
	
	//printf("%d ", current->no);
	if(root->child == NULL) {
		free(current);
	    return;	
	}
	listStart(root->child);		
	while(listNext(current->child)) {
		node_tmp = listGet(current->child);			
		dfs(node_tmp);			
	}
	free(current);
}

//初始化 header_table
struct header_table * create_header_table(struct header_table *htable, int *item_index) {	
	int i;
	for(i=0;i<MIN_SUPPORT_INDEX;i++) {
		if(i==0) {
			htable->no = *(item_index + i);
			htable->prev = NULL;
			htable->cond = listCreate();
			htable->next = NULL;
			header_head = htable;
		}
		else {
			struct header_table *new_htable = malloc(sizeof(struct header_table));
			new_htable->no = *(item_index + i);
			new_htable->prev = htable;
			new_htable->cond = listCreate();
			new_htable->next = NULL;
			htable->next = new_htable;
			htable = new_htable;
		}
	}	
	return header_head;
}

//將該點加入 header_table
struct header_table *add_header_table(struct header_table *htable, struct node *current_node, short value) {
	while(htable->no != value) {
		htable = htable->next;			
	}
	listAdd(htable->cond, current_node);
	return htable;
}

void conditional_parrern_base(struct node *fptree, struct header_table *htable, int *item_counter,int *item_index, char *generate_string) {	
	struct frequent_patterns *fp = malloc(sizeof(struct frequent_patterns));
	struct frequent_patterns *fp_head = malloc(sizeof(struct frequent_patterns));
	
	struct node *now_node = malloc(sizeof(struct node));
	int ptr_index; 
	fp_head = fp;	
	if(generate_string != "") //printf("%s \n", generate_string);
	while(htable != NULL) {			
		fp = fp_head;
		fp->next = NULL;
		fp->index = 0;
		listStart(htable->cond);		
		while(listNext(htable->cond)) {			
			now_node = listGet(htable->cond);			
			if(fp->index == 0) {
				fp->ptr  = malloc(sizeof(short) * MIN_SUPPORT_INDEX);
			}
			else {
				struct frequent_patterns *new_fp = malloc(sizeof(struct frequent_patterns));
				new_fp->ptr  = malloc(sizeof(short) * MIN_SUPPORT_INDEX);
				fp->next 	 = new_fp;
				fp 			 = new_fp;
			}
			
			fp->counter = now_node->counter;				
			fp->htable_value = htable->no;
			ptr_index   = 0;
			now_node = now_node->parent;
			while(now_node != NULL) {			
				if( now_node->no == -1) break;
				*(fp->ptr + ptr_index) = now_node->no;
				ptr_index++;
				now_node = now_node->parent;
			}						
			fp->index = ptr_index;
		}
		
		struct header_table *sub_htable = malloc(sizeof(struct header_table));		
		struct node         *sub_tree   = malloc(sizeof(struct node));			
		
		sub_tree = create_fptree();						
		sub_tree = build_sub_tree(sub_tree, sub_htable, fp_head, item_counter, item_index);
		
		//dfs(sub_tree);		
		if(sub_tree->child != NULL) {			
			int len = strlen(generate_string) + 4;	
			char *str_ans = malloc(sizeof(char) * len);	
			myString_cat(str_ans, generate_string, htable->no);			
			
			while(sub_htable->next != NULL) sub_htable = sub_htable->next;					
			
			conditional_parrern_base(sub_tree, sub_htable, item_counter, item_index,  str_ans);
			
			dfs(sub_tree);			
			
		}else if(htable->prev == NULL || listCount(htable->cond) > 0){			
			int len = strlen(generate_string) + 4;	
			char *str_ans = malloc(sizeof(char) * len);	
			myString_cat(str_ans, generate_string, htable->no);			
			//printf("%s\n", str_ans);
		}		
		
		htable = htable->prev;
	}		
	while(htable != NULL) {
		header_head = htable;
		htable 	    = htable->next;
		free(header_head);			
	}
	
}


void myString_cat(char *str_ans, char *old_string, int value) {
	int s = 0;
	int len;
	len = strlen(old_string) + 4;
	for(s=0;s<len;s++) {
		*(str_ans+s) = 0;
	}
	strcat(str_ans, old_string);
	strcat(str_ans, ",");	
	char new_string[3];
	
	sprintf(new_string, "%d", value);
	strcat(str_ans, new_string);
}

struct node * build_sub_tree(struct node *sub_tree, struct header_table *sub_htable, struct frequent_patterns *fp, int *item_counter, int *item_index) {
	struct node 			 *fptree  = malloc(sizeof(struct node));
	struct frequent_patterns *fp_head = malloc(sizeof(struct frequent_patterns));
	int i;	
	
	
	create_header_table(sub_htable, item_index);
	fp_head = fp;
	
	for(i=0;i<ITEM_COUNT;i++) *(item_counter + i) = 0;
	
	while(fp != NULL) {				
		for(i=fp->index-1;i>-1 ;i--) {	
			*(item_counter + *(fp->ptr+i)) = *(item_counter + *(fp->ptr+i)) + fp->counter;	
		}	
		fp = fp->next;
	}
		
	fp = fp_head;	
	
	fptree = sub_tree;
	while(fp != NULL) {				
		for(i=fp->index-1;i>-1 ;i--) {
			if( *(item_counter + *(fp->ptr+i)) >= MIN_SUPPORT) {	
				sub_tree = insert_node(sub_tree, *(fp->ptr+i), sub_htable, fp->counter);
				add_header_table(sub_htable, sub_tree, *(fp->ptr + i));							
			}
		}
		sub_tree = fptree;
		fp = fp->next;
	}	
	
	return fptree;
}
