#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

book create_book(int book_id, const char *title, const char *author) {
    book new_book = malloc(sizeof(struct Booklist));
    if (!new_book) {
        printf("Memory allocation failed for new book.\n");
        return NULL;
    }
    new_book->id = book_id;
    strncpy(new_book->title, title, sizeof(new_book->title) - 1);
    new_book->title[sizeof(new_book->title) - 1]='\0';
    strncpy(new_book->author, author, sizeof(new_book->author) - 1);
    new_book->author[sizeof(new_book->author) - 1]='\0';
    new_book->is_issued = 0;
    new_book->issue_date[0]='\0';
    new_book->due_date[0]='\0';
    new_book->issued_to=-1;
    new_book->next=NULL;
    return new_book;
}
void delete_book(book b) {
    free(b);
}

void display_book(book b) {
    printf("ID: %d\nTitle: %s\nAuthor: %s\nIssued: %s\n",
           b->id, b->title, b->author, b->is_issued ? "Yes" : "No");
    if (b->is_issued) {
        printf("Issue Date: %s\nDue Date: %s\nIssued To: %d\n",
               b->issue_date, b->due_date, b->issued_to);
    }
}