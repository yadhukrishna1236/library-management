#ifndef HASH_H
#define HASH_H

#include "book.h"
#define TABLE_SIZE 101

typedef struct {
    book table[TABLE_SIZE];
    int count;
} hashtable;

hashtable *create_table(void);
void destroy_table(hashtable *lib);
void library_add(hashtable *lib, book b);
book library_search_id(hashtable *lib, int id);
book library_search_title(hashtable *lib, const char *title);
void library_display(hashtable *lib);
void library_display_issued(hashtable *lib);

#endif