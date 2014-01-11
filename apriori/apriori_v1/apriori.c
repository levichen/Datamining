#include "apriori.h"

struct itemListStructArray * apriori(struct itemStructArray *item) {	
	struct itemListStructArray *item_list = get_largeItem_level2(item);		
	if(item_list->link != NULL) {
		return get_largeItem(item_list);
	}
	else {
		return item_list;
	}
	
	//return item_list;
}

struct itemListStructArray * get_largeItem_level2(struct itemStructArray *item) {
	struct itemListStructArray *item_list_array = malloc(sizeof(struct itemListStructArray));
	struct itemListStructArray *item_head       = malloc(sizeof(struct itemListStructArray));	
	
	int i, j, counter;	
	item_head->link = NULL;
	
	for(i = 0; i < MAX_SIZE; i++) {
		if(item->no[i].counter >= MIN_SUPPORT) {			
			for(j = i+1; j < MAX_SIZE; j++) {
				if(item->no[j].counter >= MIN_SUPPORT) {						
					struct linkPointer *transcation_head = malloc(sizeof(struct linkPointer));									
					counter = get_transcation(item->no[i].counter, item->no[j].counter, item->no[i].next, item->no[j].next, &transcation_head);					
					
					if(counter >= MIN_SUPPORT) {				
						struct itemListStruct *itemList_tmp    = malloc(sizeof(struct itemListStruct));
						struct linkPointer    *linkPointer_tmp = malloc(sizeof(struct linkPointer));
						
						linkPointer_tmp = link_linkPointer(i, j);
						itemList_tmp    = set_itemList(linkPointer_tmp, counter, transcation_head);	
						
						set_item_list_array(&item_list_array, &itemList_tmp, &item_head);					
					}
				}
			}
		}		
	}
	struct linkPointer *head   = malloc(sizeof(struct linkPointer));
	struct linkPointer *mNext = malloc(sizeof(struct linkPointer));
	for(i=0;i<MAX_SIZE;i++) {
		head = item->no[i].next;
		while(head != NULL) {
			mNext = head->next;
			free(head);
			head = mNext;
		}
	}
	
	//free(item);
	return item_head;
}

struct itemListStructArray * get_largeItem(struct itemListStructArray *item_list_array) {
	struct itemListStructArray *response   = malloc(sizeof(struct itemListStructArray));
    struct itemListStructArray *element1   = malloc(sizeof(struct itemListStructArray));
    struct itemListStructArray *element2   = malloc(sizeof(struct itemListStructArray));	
	struct itemListStructArray *item_head  = malloc(sizeof(struct itemListStructArray));
    struct itemListStruct      *item_list1 = malloc(sizeof(struct itemListStruct));
	struct itemListStruct      *item_list2 = malloc(sizeof(struct itemListStruct));	
    struct linkPointer         *item1      = malloc(sizeof(struct linkPointer));   	
	
	item_head->link = NULL;
	
	element1 = item_list_array;
    element2 = item_list_array->next;

	for(element1=item_list_array;element1->next != NULL;element1=element1->next) {
		item_list1 = element1->link;		
		for(element2=element1->next;element2 != NULL;element2=element2->next) {				
			item_list2 = element2->link;
			
			item1 = is_union_item(item_list1->itemList, item_list2->itemList);
			if(item1 != NULL) {						
				struct linkPointer *transcation_head = malloc(sizeof(struct linkPointer));							
				int counter = 0;
				counter = get_transcation(item_list1->counter, item_list2->counter, item_list1->transcation, item_list2->transcation, &transcation_head);
				
				if(counter >= MIN_SUPPORT) {
					struct itemListStruct *itemList_tmp = malloc(sizeof(struct itemListStruct));
					itemList_tmp = set_itemList(item1, counter, transcation_head);

					set_item_list_array(&response, &itemList_tmp, &item_head);	
				}
			}
			else {
				break;
			}					
		}
		if(item_list1->counter > 0) {
			struct linkPointer *tmp = malloc(sizeof(struct linkPointer));
			struct linkPointer *tmp2 = malloc(sizeof(struct linkPointer));
			
			tmp = item_list1->itemList;
			while(tmp != NULL) {
				tmp2 = tmp;
				tmp = tmp2->next;
				free(tmp2);			
			}
		}
		
	}
	
	if(item_head->link != NULL) {
		free(item_list_array);
		item_head = get_largeItem(item_head);		
	}
	else {
		item_head = item_list_array;
	}
	
	return item_head;
}

struct linkPointer * is_union_item(struct linkPointer *item1, struct linkPointer *item2) {
	struct linkPointer *result      = malloc(sizeof(struct linkPointer));
	struct linkPointer *result_head = malloc(sizeof(struct linkPointer));
	result->value = -1;
	
	while(item1 != NULL && item2 != NULL) {		
		if(item1->value != item2->value) {			
			break;
		}
		struct linkPointer *tmp = malloc(sizeof(struct linkPointer));
		tmp->value = item1->value;
		tmp->next  = NULL;
		if(result->value == -1) {
			result_head = tmp;			
		}
		else {
			result->next = tmp;
		}
		result = tmp;		
		item1  = item1->next;
		item2  = item2->next;
	}
	
	if(item1->next == NULL) {
		result->next = link_linkPointer(item1->value, item2->value);				
	}
	else {		
		result_head = NULL;
	}
	
	return result_head;
}


int get_transcation(int count1, int count2, struct linkPointer *transcation1, struct linkPointer *transcation2, struct linkPointer **transcation_head) {
	struct linkPointer *transcation = malloc(sizeof(struct linkPointer));
	transcation->value = -1;

	int counter = 0;
	while(transcation1 != NULL && transcation2 != NULL) {
		if(count1+counter < MIN_SUPPORT || count2+counter < MIN_SUPPORT) {
			break;
		}
		if(transcation1->value > transcation2->value) {
			transcation1 = transcation1->next;
			count1--;
		}
		else if(transcation1->value < transcation2->value){
			transcation2 = transcation2->next;
			count2--;
		}
		else {		
			set_transcation(&transcation, transcation_head, transcation1->value);
			
			transcation1 = transcation1->next;
			transcation2 = transcation2->next;
			counter++;
			count1--;
			count2--;
		}
	}
	
	/*if(counter < MIN_SUPPORT) {
		struct linkPointer *tmp = malloc(sizeof(struct linkPointer));
		tmp = transcation;
		while(tmp != NULL) {
			transcation = tmp;
			tmp = transcation->next;
			free(transcation);			
		}
		
	}*/
	return counter;
}

void set_transcation(struct linkPointer **transcation, struct linkPointer **transcation_head, int value) {
	struct linkPointer *transcation_tmp = malloc(sizeof(struct linkPointer));
	transcation_tmp->value = value;
	transcation_tmp->next  = NULL;

	if((*transcation)->value == -1) {																
		*transcation_head  = transcation_tmp;								
	}
	else {								
		(*transcation)->next = transcation_tmp;								
	}
	*transcation = transcation_tmp;
}

struct itemListStruct  * set_itemList(struct linkPointer *itemList, int counter, struct linkPointer *transcation_head) {
	struct itemListStruct  *item_list = malloc(sizeof(struct itemListStruct));
	
	item_list->itemList    = itemList;
	item_list->counter     = counter;						
	item_list->transcation = transcation_head;
	
	return item_list;
}

struct linkPointer * link_linkPointer(int value1, int value2) {
	struct linkPointer *item1 = malloc(sizeof(struct linkPointer));
	struct linkPointer *item2 = malloc(sizeof(struct linkPointer));
	
	item1->value = value1;
	item2->value = value2;
	item2->next  = NULL;
	item1->next  = item2;
	
	return item1;
}

void set_item_list_array(struct itemListStructArray **item_list_array, struct itemListStruct **item_list, struct itemListStructArray **item_head) {
	struct itemListStructArray *item_tmp = malloc(sizeof(struct itemListStructArray));
	item_tmp->link = (*item_list);
	item_tmp->next = NULL;
	
	if((*item_head)->link == NULL) {
		(*item_head) = item_tmp;
	}
	else {							
		(*item_list_array)->next = item_tmp;							
	}
	
	(*item_list_array) = item_tmp;
}

