#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    unsigned int len;
    Node *head;
    Node *tail;
} List;

void list_init(List *l);

void list_push(List *l, int v);
void list_push_back(List *l, int v);

int list_pop(List *l);
int list_pop_back(List *l);

unsigned int list_length(List *l);

void list_destroy(List *l);

#endif
