#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    unsigned int len;
    Node *head;
    Node *tail;
} List;

void list_init(List *l) { l->head = NULL; l->tail = NULL; l->len = 0; }

void list_push(List *l, int v) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node){
        new_node->value = v;
        if (l->head == NULL && l->tail == NULL && l->len == 0) { // checking if we have an empty list
            new_node->next = NULL; // setting this node's next to null bcuz this will be the only node in the list
            l->head = new_node;
            l->tail = new_node;
            l->len++;
        } else if (l->head == l->tail) {
            l->head = new_node;
            l->head->next = l->tail;
            l->len++;
        } else {
            new_node->next = l->head;
            l->head = new_node;
            l->len++;
        }
    } else {
        perror("Failed to allocate memory");
        exit(1);
    }
}

void list_push_back(List *l, int v) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node) {
        new_node->value = v;
        if (l->head == NULL && l->tail == NULL) { // checking if we have an empty list
            new_node->next = NULL; // setting this node's next to null bcuz this will be the only node in the list
            l->head = new_node;
            l->tail = new_node;
            l->len++;
        } else {
            new_node->next = NULL;
            l->tail->next = new_node;
            l->tail = new_node;
            l->len++;
        }
    } else {
        perror("Cannot allocate memory");
        exit(1); // TODO: idk if this is really needed
    }
}


int list_pop(List *l) {
    int pull;
    if (l->head == NULL && l->tail == NULL) { // if the list is empty give back a 0
        pull = 0;
    } else if (l->head == l->tail) { // if our list has only one element
        pull = l->head->value;
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->len--;
    } else {
        pull = l->head->value;
        Node *tmphead = l->head;
        l->head = l->head->next;
        free(tmphead);
        l->len--;
    }

    return pull;
}

int list_pop_back(List *l) {
    int pull;
    if (l->head == NULL && l->tail == NULL) { // if the list is empty give back a 0
        pull = 0;
    } else if (l->len == 1) { // if our list has only one element
        pull = l->tail->value;
        free(l->tail);
        l->head = NULL;
        l->tail = NULL;
        l->len--;
    } else {
        pull = l->tail->value;
        l->len--;
        Node *tmptail = l->tail;

        Node *looptail = l->head;
        Node *lasttail;
        while (looptail->next != NULL) { // after this loop, looptail should be our current tail
            lasttail = looptail;         // and lasttail should be new tail of the list
            looptail = looptail->next;
        }
        l->tail = lasttail;
        l->tail->next = NULL;
        if (l->len == 1) { // if our list has only one element after taking this out
            l->head->next = NULL; // it's the only element in the list, what would you expect?
            l->tail = l->head; // i'm such a dumb idiot
        }
        free(tmptail);
    }

    return pull;
}

unsigned int list_length(List *l) {
    return l->len;
}

void list_destroy(List *l) {
    while (l->head != NULL) {
        list_pop(l);
    }

}
