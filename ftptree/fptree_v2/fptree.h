#include "define_header.h"

struct node * create_fptree();
void 		  build_fptree(struct node *, int *, int *, struct header_table *, struct header_table *);
struct node * insert_node(struct node*, short value, struct node *, struct header_table *htable);
void 		  remove_node(struct node*, short value);
void		* node_get(list *, short , struct node *);
void 		  dfs(struct node *);
struct node * link_node(struct node *, short);
struct header_table * create_header_table(struct header_table *, struct header_table *, int *);
struct header_table * add_header_table(struct header_table *, struct node *, short);
void conditional_parrern_base(struct node *fptree, struct header_table *htable, int *item_counter, int *item_index, char *generate_string);
struct node * build_sub_tree(struct node *, struct header_table *, struct frequent_patterns *, short, int *, int*);
void myString_cat(char *re_string, char *old_string, int value);
struct node * insert_sub_node(struct node *current_node, short value, struct node *tmp, struct header_table *htable, int counter);
