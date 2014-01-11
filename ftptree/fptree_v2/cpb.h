#include "define_header.h"

void conditional_parrern_base(struct node *, struct header_table *, int *, char *);
char * myString_cat(char *, int);
struct node * build_sub_tree(struct node *sub_tree, struct header_table *sub_htable, struct frequent_patterns *fp, short htable_no, int *item_index);
struct node * insert_sub_node(struct node*, short value, struct node *, struct header_table *htable);
struct node *create_sub_fptree();
