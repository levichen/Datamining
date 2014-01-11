# include <stdio.h> 
# include <stdlib.h>
#include "define_header.h"
#include "io.h"
#include "time.h"
#include "fptree.h"

void set_define(char *, char *, char *);

int main(int argc, char * argv[]) {
	float mTime;
	clock_t start, end;
    start = clock();
	
	char *file_name = "1000k";
	char *type 	    = "rate";
	char *rate		= "1";	
	
	set_define(file_name, type, rate);
	
    int *mItem        = malloc(sizeof(int) * TRANSCATION_COUNT * SIZE_OF_ARRAY),
		*item_counter = malloc(sizeof(int) * (ITEM_COUNT + 1)), 
		*item_index   = malloc(sizeof(int) * (ITEM_COUNT + 1));		
		
	struct header_table *htable = malloc(sizeof(struct header_table));	
	
    get_dataset(mItem, item_counter, item_index);	
	
	struct node *fptree = malloc(sizeof(struct node));
	
	init();
	
	fptree = create_fptree();		
	create_header_table(htable, item_index);
	build_fptree(fptree, mItem, item_index, htable);
	
	while(htable->next != NULL) htable = htable->next;
		
	conditional_parrern_base(fptree, htable, item_counter, item_index, "");	
	
	end = clock();	
	mTime = (end-start) / (double) (CLOCKS_PER_SEC);
	mTime = mTime * 1000;
	printf("\nneed:%2.f millisecond \n", mTime);
		
    return 0;
}

void set_define(char *file_type, char *min_support_type, char *support_rate) {
	int mSupport = 0;
	float rate;
	
	strcat(FILE_PATH, DATA_SET);
	
	if(!strcmp(file_type, "1k")) {
		strcat(FILE_PATH, "T15I6N0.5KD1K.txt");	
		TRANSCATION_COUNT = 1000;
		ITEM_COUNT    	  = 500;
	}	
	else if(!strcmp(file_type, "10k")) {
		strcat(FILE_PATH, "T15I6N0.5KD10K.txt");
		TRANSCATION_COUNT = 10000;
		ITEM_COUNT    	  = 500;
	}	
	else if(!strcmp(file_type, "100k")) {
		strcat(FILE_PATH, "T15I6N0.5KD100K.txt");		
		TRANSCATION_COUNT = 100000;
		ITEM_COUNT    	  = 500;
	}	
	else if(!strcmp(file_type, "1000k")) {
		strcat(FILE_PATH, "T15I6N0.5KD1000K.txt");		
		TRANSCATION_COUNT = 1000000;
		ITEM_COUNT    	  = 500;
	}	
	else if(!strcmp(file_type, "D1")) {
		strcat(FILE_PATH, "T25I10N1KD10K.txt");	
		TRANSCATION_COUNT = 10000;
		ITEM_COUNT    	  = 1000;
	}	
	else if(!strcmp(file_type, "D2")) {
		strcat(FILE_PATH, "T25I20N10KD100K.txt");
		TRANSCATION_COUNT = 100000;
		ITEM_COUNT    	  = 10000;
	}
	else if(!strcmp(file_type, "test")) {
		strcat(FILE_PATH, "fptest.txt");
		TRANSCATION_COUNT = 5;
		ITEM_COUNT    	  = 500;
	}
	else if(!strcmp(file_type, "debug")) {
		strcat(FILE_PATH, "debug.txt");
		TRANSCATION_COUNT = 95;
		ITEM_COUNT    	  = 50;
	}
	
    if(!strcmp(min_support_type, "rate")) {
        rate = atoi(support_rate) / 100.0;
	    MIN_SUPPORT = (int) TRANSCATION_COUNT * rate;		
    }
    else {
        MIN_SUPPORT = atoi(support_rate);
    }  

	SIZE_OF_ARRAY = ITEM_COUNT / 31;
	if(ITEM_COUNT % 31 != 0) SIZE_OF_ARRAY++;	
}



