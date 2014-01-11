#include "list.h"
#include <stdlib.h>

typedef struct s_element
{
  void* data;
  struct s_element* next;
} element;

struct s_list
{
  element *top,
          *curr;
};

list* listCreate()
{
  list* res = (list*)malloc(sizeof(list));
  res->curr = res->top = (element*)calloc(1, sizeof(element));
  return res;
}

void listDelete(list* src)
{
  while ((src->curr = src->top->next))
  {
    free(src->top);
    src->top = src->curr;
  }
  
  free(src->top);
  free(src);
}

void listAdd(list* src, const void* data)
{
  element* nE = (element*)malloc(sizeof(element));
  nE->data = (void*)data;
  nE->next = src->curr->next;
  src->curr = src->curr->next = nE;
}

void listRemove(list* src)
{
  element* tmp = src->curr;
  
  if (src->top == tmp)
    tmp = tmp->next;
  if (src->top->next == tmp)
    src->top->next = tmp->next;
  
  src->curr = tmp->next;
  free(tmp);
}

void* listGet(list* src)
{
  return src->curr->data;
}

int listNext(list* src)
{
  if (src->curr->next)
  {
    src->curr = src->curr->next;
    return 1;
  }
  return 0;
}

void listStart(list* src)
{
  src->curr = src->top;
}

int listCount(list* src)
{
  int res = 0;
  element* tmp = src->top;
  
  while ((tmp = tmp->next))
    ++res;
  
  return res;
}

int listIsEmpty(list* src)
{
  if (src->top->next)
    return 0;
  return 1;
}
