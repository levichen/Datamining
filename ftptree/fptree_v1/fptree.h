#include "define_header.h"

struct node * create_fptree();
void build_fptree(struct node *, int *, int *, int *);
struct node * insert_node(struct node*, short value, struct node *);
void remove_node(struct node*, short value);
