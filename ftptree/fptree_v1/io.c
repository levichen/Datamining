#include "io.h"

//input
void get_dataset(int *mItem, int *item_counter, int *item_index, int *mPow) {
    char buffer[1024];
    char *ptr;
    int  transcation_counter = 0;
    int  mN, transcation_index, index, bit_index, i;

	
    FILE *file = fopen(FILE_PATH, "r");
    while(fgets(buffer, BUF_SIZE, file) != NULL) {		
        ptr 			  = buffer;
        mN  			  = atoi(ptr);	
		
		transcation_index = transcation_counter * SIZE_OF_ARRAY;
        put_value_to_item(mItem, item_counter, mPow,  transcation_index, mN);
        while( (ptr = strchr(ptr, ',')) != NULL && *(ptr+1) != '\n') {
            ptr++;			
            mN = atoi(ptr++); 
			put_value_to_item(mItem, item_counter, mPow, transcation_index, mN);
        }
        transcation_counter++;
    }
	fclose(file);
	//show_item(mItem);
		
	for(i=0;i<ITEM_COUNT;i++) {
		*(item_index+i) = i;	
	}
	sort_item_index(item_counter, item_index);
	/*for(i=0;i<30;i++) {
		printf("%d:%d \n", *(item_index+i), *(item_counter + i));
	} */  
}

void sort_item_index(int *item_counter, int *item_index) {
	int low, hight;
	low   = 0;
	hight = ITEM_COUNT; 
	sort(item_counter, item_index, 0, low, hight);
}

void sort(int *item_counter, int *item_index, int deep, int low, int hight) {
	int middIndex = 0;
	if(low<hight) {
		middIndex = partition(item_counter, item_index, low, hight, deep);		
		sort(item_counter, item_index, deep+1, low, middIndex-1);
		
		if(deep!= 0) {			
			sort(item_counter, item_index, deep+1, middIndex+1, hight);
		}
	}
}

int partition(int *item_counter, int *item_index, int low, int hight, int deep) {
	int middValue, middIndex;
		
	middValue = *(item_counter + low);
	middIndex = low;
	if(deep == 0) {
		middValue = MIN_SUPPORT;
	}
	
	while(low <= hight) {
		for(; low < hight && *(item_counter + hight) < middValue;hight--);
		if(low <= hight) {
			swap(item_counter, middIndex, hight);
			swap(item_index, middIndex, hight);
			middIndex = hight;
			low++;
		}
		for(; low < hight && *(item_counter + low) >= middValue; low++);
		if(low <= hight) {
			if(*(item_counter + low) == middValue && *(item_index + low) > middIndex) {
				
			}
			else {
				swap(item_counter, low, middIndex);
				swap(item_index, low, middIndex);
				middIndex = low;
			}
			hight--;
		}
	}
	return middIndex;
}

void swap(int *arr, int low, int hight) {
	int tmp;
	tmp = *(arr + low);
	*(arr + low) = *(arr + hight);
	*(arr + hight) = tmp;
}

void put_value_to_item(int *mItem, int *item_counter, int *mPow, int transcation_index, int mN) {
	int index, bit_index;
	
	index     = mN / 31;		
	bit_index = mN % 31;		
	
	if(mN == 0) {
		bit_index = 1;
	}
	else {
		bit_index++;
	}
	
	index                += transcation_index;		
	*(mItem + index)     = *(mItem + index) + *(mPow + bit_index);
	*(item_counter + mN) = *(item_counter + mN) + 1; 
}

void show_item(int *mItem) {
    int i, j;
    for(i=0;i<5;i++) {
        printf("%d->", i);
        for(j=0;j<17;j++) {
            printf("%d ", *(mItem + i*17+j));
        }
        puts("\n");
    }
}
