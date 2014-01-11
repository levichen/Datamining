#include "define_header.h"
#include "io.h"
#include "apriori.h"

#include "time.h"
void set_define(char *, char *, char *);
int get_itemset_counter(struct itemListStructArray *);
int get_itemset_level2_counter(struct itemStructArray *);
int main(int argc, char * argv[]) {

	clock_t start, end;
    start = clock();
	set_define(argv[1], argv[2], argv[3]);
	
    struct itemStructArray *item = get_dataset();
    
	struct itemListStructArray *result = apriori(item);
    /*if(result->link == NULL) {
        printf("只在第一層");
    }
    else {
        show_largeItem_level1(result);
    }*/

    int counter;
    
    /*if(result->link == NULL) {
        counter = get_itemset_level2_counter(item);
    }
    else {
        counter = get_itemset_counter(result);
    }
    printf("counter is: %d\n", counter);*/
    
	end = clock();
	float mTime;
	mTime = (end-start)/(double)(CLOCKS_PER_SEC);
	mTime = mTime * 1000;
    printf("%.2f\n", mTime);
	
    return 0;
}

int get_itemset_level2_counter(struct itemStructArray *result) {
    int i = 0, counter = 0;
    for(i=0;i<=MAX_SIZE;i++) {
        if(result->no[i].counter >= MIN_SUPPORT) {
            counter++;
        }
    }
    return counter;
}

int get_itemset_counter(struct itemListStructArray *result) {
    int counter =0;
    while(result != NULL && result->link != NULL) {
        counter++;
        result = result->next;
    }
    return counter;
}

void set_define(char *file_type, char *min_support_type, char *support_rate) {
	int mSupport = 0;
	int tranacation_counter = 0;
	float rate;
	
	strcat(FILE_PATH, DATA_SET);
	
	if(!strcmp(file_type, "1k")) {
		strcat(FILE_PATH, "T15I6N0.5KD1K.txt");	
		tranacation_counter = 1000;
	}	
	else if(!strcmp(file_type, "10k")) {
		strcat(FILE_PATH, "T15I6N0.5KD10K.txt");
		tranacation_counter = 10000;
	}	
	else if(!strcmp(file_type, "100k")) {
		strcat(FILE_PATH, "T15I6N0.5KD100K.txt");		
		tranacation_counter = 100000;
	}	
	else if(!strcmp(file_type, "1000k")) {
		strcat(FILE_PATH, "T15I6N0.5KD1000K.txt");		
		tranacation_counter = 1000000;
	}	
	else if(!strcmp(file_type, "D1")) {
		strcat(FILE_PATH, "T25I10N1KD10K.txt");	
		tranacation_counter = 10000;
	}	
	else if(!strcmp(file_type, "D2")) {
		strcat(FILE_PATH, "T25I20N10KD100K.txt");
		tranacation_counter = 100000;
	}
	else if(!strcmp(file_type, "test")) {
		strcat(FILE_PATH, "test.txt");
		tranacation_counter = 10;
	}
	else if(!strcmp(file_type, "debug")) {
		strcat(FILE_PATH, "debug.txt");
		tranacation_counter = 95;
	}
	
    if(!strcmp(min_support_type, "rate")) {
        rate = atoi(support_rate) / 100.0;
	    MIN_SUPPORT = (int) tranacation_counter * rate;		
    }
    else {
        MIN_SUPPORT = atoi(support_rate);
    }
    //printf("FILE PATH: %s\n", FILE_PATH);
    //printf("MIN SUPPORT: %d\n", MIN_SUPPORT);
}

