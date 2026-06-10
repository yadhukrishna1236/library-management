#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "hash.h"

void save_books(hashtable *lib, const char *filename);
hashtable *load_books(const char *filename);

#endif