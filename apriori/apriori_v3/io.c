#include "io.h"

//input
struct itemStructArray * get_dataset() {
    struct itemStructArray *item = malloc(sizeof(struct itemStructArray));
    char buffer[1024];
    char *ptr;
    int item_no;
    int transcation_counter = 0;

    FILE *file = fopen(FILE_PATH, "r");
   
    while(fgets(buffer, BUF_SIZE, file) != NULL) {
        transcation_counter++;        
        ptr = buffer;

        item_no = atoi(ptr);
        item->no[item_no] = link_transcation_of_item(item->no[item_no], transcation_counter);
      
        while( (ptr = strchr(ptr, ',')) != NULL && *(ptr+1) != '\n' ) {
            ptr++;
            item_no = atoi(ptr++);
            item->no[item_no] = link_transcation_of_item(item->no[item_no], transcation_counter);
        }
		
    }
    fclose(file);
    return item;
}

struct itemStruct link_transcation_of_item (struct itemStruct item, int value) {
    struct linkPointer *transcation = malloc(sizeof(struct linkPointer));
    item.counter++;
    transcation->value = value;
    if(item.counter == 1) {
        transcation->next = NULL;
    }
    else {
        transcation->next = item.next;
    }
    item.next = transcation;
    return item;
}


//output
void show_all_itemArray(struct itemStructArray *item) {
    struct linkPointer *tmp;
    int i=0;
    for(i=0;i<MAX_SIZE;i++) {
        if(item->no[i].counter) {
            printf("  %d  |  %d  |  ", i, item->no[i].counter);    
            tmp = item->no[i].next;
            while(tmp != NULL) {
                printf("%d ", tmp->value);
                tmp = tmp->next;
            }
            puts("\n");
        }
    }
}

void show_largeItem_level1(struct itemListStructArray *item_list) {	
	while(item_list != NULL) {
		struct itemListStruct *s1 = malloc(sizeof(struct itemListStruct));
		struct linkPointer *t1 = malloc(sizeof(struct linkPointer));
		struct linkPointer *t2 = malloc(sizeof(struct linkPointer));
			
		s1 = item_list->link;
		t1 = s1->itemList;
		while(t1 != NULL) {
			printf("%d, ", t1->value);
			t1 = t1->next;
		}
		
		printf("| %d | ", s1->counter);
		
		t2 = s1->transcation;
		while(t2 != NULL) {
			printf("%d, ", t2->value);
			t2 = t2->next;
		}
		
		puts("\n");
		item_list = item_list->next;
	}
}
