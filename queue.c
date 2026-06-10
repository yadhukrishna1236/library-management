#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

queue create_queue(void) {
    queue q = malloc(sizeof(struct QueueStruct));
    if (q) {
        q->front = NULL;
        q->rear = NULL;
        q->count = 0;
    }
    return q;
}

void destroy_queue(queue q) {
    if (!q) return;
    QNode curr = q->front;
    while (curr) {
        QNode temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);
}

void enqueue(queue q,int book_id,int student_id,const char *student_name) {
    if (!q) return;
    QNode new_node = malloc(sizeof(struct WaitNode));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->book_id =book_id;
    new_node->student_id=student_id;
    strncpy(new_node->student_name, student_name, sizeof(new_node->student_name) - 1);
    new_node->student_name[sizeof(new_node->student_name) - 1]='\0';
    new_node->next=NULL;
    if (!q->rear) {
        q->front=q->rear=new_node;
    } else {
        q->rear->next=new_node;
        q->rear=new_node;
    }
    q->count++;
}

void dequeue_specific(queue q, int book_id, int student_id, const char *student_name) {
    if (!q || !q->front) return;
    QNode curr = q->front;
    if (curr->book_id==book_id && curr->student_id==student_id && 
        strcmp(curr->student_name, student_name)==0) {
        q->front=curr->next;
        if (!q->front) q->rear=NULL;
        free(curr);
        q->count--;
        return;
    }
    while (curr->next) {
        if (curr->next->book_id==book_id && curr->next->student_id == student_id &&
            strcmp(curr->next->student_name, student_name)==0) {
            QNode to_delete=curr->next;
            curr->next=to_delete->next;
            if (to_delete==q->rear) q->rear=curr;
            free(to_delete);
            q->count--;
            return;
        }
        curr=curr->next;
    }
}

void display_waitlist(queue q,int book_id) {
    if (!q || !q->front) {
        printf("No waitlist for book ID %d.\n", book_id);
        return;
    }
    printf("\n--- Waitlist for Book ID %d ---\n", book_id);
    int found=0, pos = 1;
    QNode temp=q->front;
    while(temp) {
        if (temp->book_id == book_id) {
            printf("%d. Student ID: %d, Name: %s\n", pos, temp->student_id, temp->student_name);
            found = 1;
            pos++;
        }
        temp=temp->next;
    }
    if (!found)printf("No waitlist for book ID %d.\n", book_id);
}
int in_waitlist(queue q,int book_id,int student_id,const char *student_name) {
    if (!q) return 0;
    QNode temp=q->front;
    while (temp) {
        if (temp->book_id == book_id && temp->student_id == student_id &&
            strcmp(temp->student_name, student_name) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}