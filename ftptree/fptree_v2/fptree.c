#include "fptree.h"

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
void build_fptree(struct node *fptree, int *mItem, int *item_index, struct header_table *htable, struct header_table *head) {	
	int i, j, transcation_counter, value;
	int index, bit_index;
	
	struct node *root = malloc(sizeof(struct node));
	struct node *tmp  = malloc(sizeof(struct node));
	htable = create_header_table(htable, head, item_index);
	root = fptree;	
	head = htable;
	
	for(i=0;i < TRANSCATION_COUNT;i++) {				
		transcation_counter = i * SIZE_OF_ARRAY;		
		for(j=0;j<MIN_SUPPORT_INDEX;j++) {						
			value 	  = *(item_index + j);			
			index     = value / 31 + transcation_counter;			
			bit_index = value % 31;
			
			bit_index++;
			if(value == 0) bit_index = 1;			
			
			if((*(mItem + index) >> (bit_index-1)) & 1) {				
				fptree = insert_node(fptree, value, tmp, htable);										
			}			
		}
		fptree = root;				
		htable = head;
	}		
	//htable = head;
	free(mItem);
	//free(item_index);
}

//插入樹結點
struct node * insert_node(struct node *current_node, short value, struct node *tmp, struct header_table *htable) {		
	if(current_node->child == NULL) {
		//list *new_list 	      = listCreate(0);		
		current_node->child   = listCreate();
		current_node 		  = link_node(current_node, value);	
		add_header_table(htable, current_node, value);
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

//深度優先排序法
void dfs(struct node *root) {
	struct node *current = malloc(sizeof(struct node));
	struct node *tmp 	 = malloc(sizeof(struct node));
	current = root;
	
	printf("%d ", current->no);
	if(root->child == NULL) return;	
	listStart(root->child);		
	while(listNext(current->child)) {
		tmp = listGet(current->child);			
		dfs(tmp);
	}
}

//初始化 header_table
struct header_table * create_header_table(struct header_table *htable, struct header_table *head, int *item_index) {	
	int i;
	for(i=0;i<MIN_SUPPORT_INDEX;i++) {
		if(i==0) {
			htable->no = *(item_index + i);
			htable->prev = NULL;
			htable->cond = listCreate();
			htable->next = NULL;
			head = htable;
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
	return head;
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
		/*
		while(fp_head != NULL) {
			int i;
			for(i=0;i<fp_head->index;i++) {
				printf("%d ", *(fp_head->ptr + i));
			}
			puts("\n");
			fp_head = fp_head->next;
		}*/
		
		struct header_table *sub_htable = malloc(sizeof(struct header_table));			
		struct node         *sub_tree   = malloc(sizeof(struct node));			
		
		sub_tree = create_fptree();						
		sub_tree = build_sub_tree(sub_tree, sub_htable, fp_head, htable->no, item_counter, item_index);
		
		//dfs(sub_tree);		
		if(sub_tree->child != NULL) {			
			int len = strlen(generate_string) + 4;	
			char *str_ans = malloc(sizeof(char) * len);	
			myString_cat(str_ans, generate_string, htable->no);			
			
			while(sub_htable->next != NULL) sub_htable = sub_htable->next;					
			
			conditional_parrern_base(sub_tree, sub_htable, item_counter, item_index,  str_ans);
			free(sub_tree);
			free(sub_htable);
		}else if(htable->prev == NULL || listCount(htable->cond) > 0){			
			int len = strlen(generate_string) + 4;	
			char *str_ans = malloc(sizeof(char) * len);	
			myString_cat(str_ans, generate_string, htable->no);			
			//printf("%s\n", str_ans);
		}
		
		//printf("%d ", htable->no);
		htable = htable->prev;		
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

struct node * build_sub_tree(struct node *sub_tree, struct header_table *sub_htable, struct frequent_patterns *fp, short htable_no, int *item_counter, int *item_index) {
	struct node *fptree = malloc(sizeof(struct node));
	int i;	
	
	struct header_table *head = malloc(sizeof(struct header_table));
	struct node *tmp = malloc(sizeof(struct node));
	create_header_table(sub_htable, head, item_index);	
	struct frequent_patterns *fp_head = malloc(sizeof(struct frequent_patterns));
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
				//printf("%d", *(item_counter);
				sub_tree = insert_sub_node(sub_tree, *(fp->ptr+i), tmp, sub_htable, fp->counter);
				add_header_table(sub_htable, sub_tree, *(fp->ptr + i));							
			}
		}
		sub_tree = fptree;
		fp = fp->next;
	}
	
	
	return fptree;
}

//插入樹結點
struct node * insert_sub_node(struct node *current_node, short value, struct node *tmp, struct header_table *htable, int counter) {		
	if(current_node->child == NULL) {
		//list *new_list 	      = listCreate(0);		
		current_node->child   = listCreate();
		current_node 		  = link_node(current_node, value);	
		current_node->counter = counter;
		add_header_table(htable, current_node, value);
	}
	else {
		tmp = node_get(current_node->child, value, tmp);
		if(tmp != NULL) {
			current_node 		  = tmp;
			current_node->counter = current_node->counter + counter;
		}
		else {			
			current_node = link_node(current_node, value);
			add_header_table(htable, current_node, value);
			current_node->counter = counter;
		}
	}
		
	return current_node;
}
