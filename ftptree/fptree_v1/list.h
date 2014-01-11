#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

/** List structure (forward declaration). */
struct s_list;
typedef struct s_list list;

/** Creates a new list. */
extern list* listCreate();

/** Frees the memory for the list structure. */
extern void  listDelete(list* src);

/** Adds a new datum after the current position. */
extern void  listAdd(list* src, const void* data);

/** Removes the currently selected item. */
extern void  listRemove(list* src);

/** Returns the currently selected element. */
extern void* listGet(list* src);

/** Advances the list one position and returns 1, if the end wasn't reached. */
extern int   listNext(list* src);

/** Sets the current element to the top.
    This is always one element before the first one. */
extern void  listStart(list* src);

/** Counts the list. */
extern int   listCount(list* src);

/** Returns 1, if this list is empty, else 0. */
extern int   listIsEmpty(list* src);

#endif
