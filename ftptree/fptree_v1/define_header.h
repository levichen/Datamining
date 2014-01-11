#ifndef DEFINE_HEADER_H_INCLUDED
#define DEFINE_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"

//#define DATA_SET "/home/levis/Datamining/dataset/T15I6N0.5KD1K.txt"
#define DATA_SET "/home/levis/Datamining/dataset/"
#define BUF_SIZE 1024
#define MAX_SIZE 10000

int   TRANSCATION_COUNT;
int   SIZE_OF_ARRAY;
short ITEM_COUNT;
int   MIN_SUPPORT;
char  FILE_PATH[100];

struct node {
    short no;
	struct node *parent;
	int counter;
	hashmap *child;
};

#endif
