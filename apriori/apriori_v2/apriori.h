#include "define_header.h"

struct itemListStructArray *apriori(struct itemStructArray *item);
struct itemListStructArray * get_largeItem_level2(struct itemStructArray *);
void set_transcation(struct linkPointer **, struct linkPointer **, int);
struct itemListStruct  * set_itemList(struct linkPointer *, int, struct linkPointer *);
void set_item_list_array(struct itemListStructArray **, struct itemListStruct **, struct itemListStructArray **);
struct itemListStructArray * get_largeItem(struct itemListStructArray *);
struct linkPointer * is_union_item(struct linkPointer *, struct linkPointer *);
struct linkPointer * link_linkPointer(int, int);
int get_transcation(int, int, struct linkPointer *, struct linkPointer *, struct linkPointer **);
