#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hash(int id) {
    return id % TABLE_SIZE;
}

hashtable *create_table(void) {
    hashtable *ht = malloc(sizeof(hashtable));
    if (ht) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            ht->table[i] = NULL;
        }
        ht->count = 0;
    }
    return ht;
}

void destroy_table(hashtable *lib) {
    if (!lib) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        book curr = lib->table[i];
        while (curr) {
            book temp = curr;
            curr = curr->next;
            delete_book(temp);
        }
    }
    free(lib);
}

void library_add(hashtable *lib, book b) {
    if (!lib || !b) return;
    if (library_search_id(lib, b->id)) {
        printf("Book with ID %d already exists.\n", b->id);
        return;
    }
    int index = hash(b->id);
    b->next = lib->table[index];
    lib->table[index] = b;
    lib->count++;
}

book library_search_id(hashtable *lib, int id) {
    if (!lib) return NULL;
    int index = hash(id);
    book curr = lib->table[index];
    while (curr) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

book library_search_title(hashtable *lib, const char *title) {
    if (!lib) return NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        book curr = lib->table[i];
        while (curr) {
            if (strcmp(curr->title, title) == 0) return curr;
            curr = curr->next;
        }
    }
    return NULL;
}

void library_display(hashtable *lib) {
    if (!lib) return;
    printf("\n--- All Books ---\n");
    if (lib->count == 0) {
        printf("Library is empty.\n");
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        book curr = lib->table[i];
        while (curr) {
            display_book(curr);
            printf("-----------------\n");
            curr = curr->next;
        }
    }
}

void library_display_issued(hashtable *lib) {
    if (!lib) return;
    printf("\n--- Issued Books ---\n");
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        book curr = lib->table[i];
        while (curr) {
            if (curr->is_issued) {
                display_book(curr);
                found = 1;
                printf("-----------------\n");
            }
            curr = curr->next;
        }
    }
    if (!found) printf("No books currently issued.\n");
}