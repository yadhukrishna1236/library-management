#ifndef QUEUE_H
#define QUEUE_H

struct WaitNode {
    int book_id;
    int student_id;
    char student_name[51];
    struct WaitNode *next;
};
typedef struct WaitNode* QNode;


struct QueueStruct {
    QNode front;
    QNode rear;
    int count;
};
typedef struct QueueStruct* queue;

queue create_queue(void);
void destroy_queue(queue q);
void enqueue(queue q, int book_id, int student_id, const char *student_name);
void dequeue_specific(queue q, int book_id, int student_id, const char *student_name);
void display_waitlist(queue q, int book_id);
int in_waitlist(queue q, int book_id, int student_id, const char *student_name);

#endif