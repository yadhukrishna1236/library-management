#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "book.h"
#include "hash.h"
#include "queue.h"
#include "stack.h"
#include "file_handler.h"

void clear_input_buffer(void){
 int c;
 while((c=getchar())!='\n'&&c!=EOF);
}

int main(void){
 hashtable *lib=load_books("library.dat");
 queue waitlist=create_queue();
 stack history=create_stack();
 int choice;

 do{
  printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
  printf("1.  Add Book\n");
  printf("2.  Display All Books\n");
  printf("3.  Search Book by ID\n");
  printf("4.  Search Book by Title\n");
   printf("5.  Issue Book\n");
  printf("6.  Return Book\n");
  printf("7.  Display Issued Books\n");
  printf("8.  Add to Waitlist\n");
  printf("9.  Display Waitlist\n");
  printf("10. View Transaction History\n");
  printf("11. View Last N Transactions\n");
  printf("12. Save and Exit\n");
  printf("Enter choice: ");

  if(scanf("%d",&choice)!=1){
   clear_input_buffer();
   printf("Invalid input. Please enter a number.\n");
   continue;
  }

  clear_input_buffer();

  int id,sid,fine;
  char title[51],author[51],sname[51],date[11];
  book b;

  switch(choice){

   case 1:
    printf("Enter Book ID: ");
    scanf("%d",&id);
    clear_input_buffer();

    printf("Enter Title: ");
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")]=0;

    printf("Enter Author: ");
    fgets(author,sizeof(author),stdin);
    author[strcspn(author,"\n")]=0;

    b=create_book(id,title,author);
    if(b) library_add(lib,b);
    break;

   case 2:
    library_display(lib);
    break;

   case 3:
    printf("Enter Book ID: ");
    scanf("%d",&id);

    b=library_search_id(lib,id);

    if(b) display_book(b);
    else printf("Book not found.\n");
    break;

   case 4:
    printf("Enter Title: ");
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")]=0;

    b=library_search_title(lib,title);

    if(b) display_book(b);
    else printf("Book not found.\n");
    break;

   case 5:
    printf("Enter Book ID to issue: ");
    scanf("%d",&id);

    printf("Enter Student ID: ");
    scanf("%d",&sid);

    clear_input_buffer();

    printf("Enter Student Name: ");
    fgets(sname,sizeof(sname),stdin);
    sname[strcspn(sname,"\n")]=0;

    printf("Enter Due Date (YYYY-MM-DD): ");
    fgets(date,sizeof(date),stdin);
    date[strcspn(date,"\n")]=0;

    b=library_search_id(lib,id);

    if(!b){
     printf("Book not found.\n");
    }
    else if(b->is_issued){
     printf("Book is already issued.\n");
    }
    else{
     b->is_issued=1;
     b->issued_to=sid;
     strncpy(b->due_date,date,10);
     b->due_date[10]='\0';

     time_t now=time(NULL);
     struct tm *t=localtime(&now);

     snprintf(b->issue_date,11,"%04d-%02d-%02d",
              t->tm_year+1900,t->tm_mon+1,t->tm_mday);

     push_transaction(history,TRANS_ISSUE,id,sid,0);
     printf("Book issued successfully.\n");
    }
    break;

   case 6:
    printf("Enter Book ID to return: ");
    scanf("%d",&id);

    printf("Enter fine amount (0 if none): ");
    scanf("%d",&fine);

    b=library_search_id(lib,id);

    if(!b){
     printf("Book not found.\n");
    }
    else if(!b->is_issued){
     printf("Book is not issued.\n");
    }
    else{
     push_transaction(history,TRANS_RETURN,id,b->issued_to,fine);
     b->is_issued=0;
     b->issued_to=-1;
     b->issue_date[0]='\0';
     b->due_date[0]='\0';
     printf("Book returned successfully.\n");
    }
    break;

   case 7:
    library_display_issued(lib);
    break;

   case 8:
    printf("Enter Book ID: ");
    scanf("%d",&id);

    printf("Enter Student ID: ");
    scanf("%d",&sid);

    clear_input_buffer();

    printf("Enter Student Name: ");
    fgets(sname,sizeof(sname),stdin);
    sname[strcspn(sname,"\n")]=0;

    enqueue(waitlist,id,sid,sname);
    printf("Added to waitlist.\n");
    break;

   case 9:
    printf("Enter Book ID: ");
    scanf("%d",&id);
    display_waitlist(waitlist,id);
    break;

   case 10:
    display_history(history);
    break;

   case 11:
    printf("Enter N: ");
    scanf("%d",&id);
    display_last_n(history,id);
    break;

   case 12:
    save_books(lib,"library.dat");
    printf("Goodbye!\n");
    break;

   default:
    printf("Invalid choice.\n");
  }

 }while(choice!=12);

 destroy_stack(history);
 destroy_queue(waitlist);
 destroy_table(lib);

 return 0;
}