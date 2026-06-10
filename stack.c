#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

stack create_stack(void){
    stack s=malloc(sizeof(struct StackStruct));
    if(s){
        s->top=NULL;
        s->count=0;
    }
    return s;
}

void destroy_stack(stack s){
    if(!s) return;

    SNode curr=s->top;
    while(curr){
        SNode temp=curr;
        curr=curr->next;
        free(temp);
    }
    free(s);
}

void push_transaction(stack s,int type,int book_id,int student_id,int fine){
    if(!s) return;

    SNode temp=malloc(sizeof(struct TransNode));
    if(!temp){
        printf("Memory allocation failed.\n");
        return;
    }

    temp->type=type;
    temp->book_id=book_id;
    temp->student_id=student_id;
    temp->fine_amount=fine;

    time_t now=time(NULL);
    struct tm *t=localtime(&now);

    snprintf(temp->date,MAX_DATE,"%04d-%02d-%02d",
             t->tm_year+1900,t->tm_mon+1,t->tm_mday);

    temp->next=s->top;
    s->top=temp;
    s->count++;
}

void display_history(stack s){
    if(!s||!s->top){
        printf("No transactions yet.\n");
        return;
    }

    SNode curr=s->top;
    printf("\n--- Transaction History ---\n");

    while(curr){
        printf("Type: %s, Book ID: %d, Student ID: %d, Date: %s, Fine: %d\n",
               curr->type==TRANS_ISSUE?"Issue":"Return",
               curr->book_id,curr->student_id,curr->date,curr->fine_amount);
        curr=curr->next;
    }
}

void display_last_n(stack s,int n){
    if(!s||!s->top||n<=0) return;

    printf("\n--- Last %d Transactions ---\n",n);

    SNode curr=s->top;
    int i=0;

    while(curr&&i<n){
        printf("Type: %s, Book ID: %d, Student ID: %d, Date: %s, Fine: %d\n",
               curr->type==TRANS_ISSUE?"Issue":"Return",
               curr->book_id,curr->student_id,curr->date,curr->fine_amount);
        curr=curr->next;
        i++;
    }
}