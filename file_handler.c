#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_books(hashtable *lib, const char *filename) {
    if (lib==NULL) return;
    FILE *fp=fopen(filename,"w");
    if(!fp){
        printf("Error opening file for writing.\n");
        return;
    }
    for(int i=0;i<TABLE_SIZE;i++){
      book curr=lib->table[i];
    while(curr){
        fprintf(fp, "%d|%s|%s|%d|%s|%s|%d\n",curr->id, curr->title, curr->author, curr->is_issued,curr->issue_date, curr->due_date, curr->issued_to);
        curr=curr->next;
    }
      
    }
      fclose(fp);
      printf("Library data saved successfully.\n");  
        
    }

    hashtable *load_books(const char *filename) {
      hashtable *lib=create_table();
      FILE *fp=fopen(filename,"r");
      if(!fp){
        printf("Error opening file for reading.\n");
        return lib;}

            char line[300];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        book b = malloc(sizeof(struct Booklist));
        if (!b) continue;
        char *token = strtok(line, "|");
        if (!token) { free(b); continue; }
        b->id = atoi(token);
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; }
          strncpy(b->title, token, 50); b->title[50]='\0';
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; }
         strncpy(b->author, token, 50); b->author[50]= '\0';
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; }
         b->is_issued = atoi(token);
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; 
        }
        strncpy(b->issue_date, token, 10); b->issue_date[10]='\0';
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; }
         strncpy(b->due_date, token, 10); b->due_date[10]= '\0';
        token = strtok(NULL, "|");
        if (!token) { free(b); continue; }
        b->issued_to = atoi(token);
        b->next = NULL;
        library_add(lib, b);
    }
    fclose(fp);
    printf("Library data loaded successfully. Total books: %d\n", lib->count);
    return lib;
      }
    
