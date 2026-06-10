#ifndef STACK_H
#define STACK_H

#define MAX_DATE 11
#define TRANS_ISSUE 1
#define TRANS_RETURN 2

struct TransNode {
    int type;
    int book_id;
    int student_id;
    int fine_amount;
    char date[MAX_DATE];
    struct TransNode *next;
};

typedef struct TransNode* SNode;

struct StackStruct {
    SNode top;
    int count;
};

typedef struct StackStruct* stack;

stack create_stack(void);
void destroy_stack(stack s);
void push_transaction(stack s, int type, int book_id, int student_id, int fine);
void display_history(stack s);
void display_last_n(stack s, int n);

#endif