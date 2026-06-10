#ifndef BOOK_H
#define BOOK_H

struct Booklist {
    int id;
    char title[51];
    char author[51];
    int is_issued;
    char issue_date[11];
    char due_date[11];
    int issued_to;
    struct Booklist *next;
};

typedef struct Booklist* book;

book create_book(int book_id, const char *title, const char *author);
void delete_book(book b);
void display_book(book b);

#endif