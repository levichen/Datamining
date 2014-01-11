#ifndef DEFINE_HEADER_H_INCLUDED
#define DEFINE_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define DATA_SET "/home/levis/Datamining/dataset/T15I6N0.5KD1K.txt"
#define DATA_SET "/home/levis/Datamining/dataset/"
#define BUF_SIZE 1024
#define MAX_SIZE 10000

//#define MIN_SUPPORT 10

int MIN_SUPPORT;
char FILE_PATH[100];

struct linkPointer {
    int value;
    struct linkPointer *next;
};

struct itemStruct {
    int counter;
    struct linkPointer *next;
};

struct itemStructArray {
    struct itemStruct no[MAX_SIZE];
};

struct itemListStruct {
    struct linkPointer *itemList;
    int counter;
    struct linkPointer *transcation;
};

struct itemListStructArray {
    struct itemListStruct *link;
    struct itemListStructArray *next;
};

#endif
