#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

void list_init(List *l) { l->head = NULL; l->tail = NULL; l->len = 0; }

void list_push(List *l, int v) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node){
        new_node->value = v;
        if (l->len == 0) { // if list is empty
            new_node->next = NULL;
            new_node->prev = NULL;

            l->head = new_node;
            l->tail = new_node;

            l->len++;
        } else if (l->len == 1) { // if there's only a single item
            Node *new_head = new_node;
            Node *new_tail = l->head;

            new_head->next = new_tail;
            new_head->prev = NULL;

            new_tail->next = NULL;
            new_tail->prev = new_head;

            l->head = new_head;
            l->tail = new_tail;

            l->len++;
        } else { // otherwise the list has multiple elements
            Node *new_head = new_node;
            Node *old_head = l->head;

            new_head->next = old_head;
            new_head->prev = NULL;

            old_head->prev = new_head;

            l->head = new_head;

            l->len++;
        }
    } else {
        perror("Failed to allocate memory");
        exit(1);
    }
}

void list_push_back(List *l, int v) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node){
        new_node->value = v;
        if (l->len == 0) { // if list is empty
            new_node->next = NULL;
            new_node->prev = NULL;

            l->head = new_node;
            l->tail = new_node;

            l->len++;
        } else if (l->len == 1) { // if there's only a single item
            Node *new_tail = new_node;
            Node *new_head = l->head;

            new_head->next = new_tail;
            new_head->prev = NULL;

            new_tail->next = NULL;
            new_tail->prev = new_head;

            l->head = new_head;
            l->tail = new_tail;

            l->len++;
        } else { // otherwise the list has multiple elements
            Node *new_tail = new_node;
            Node *old_tail = l->tail;

            new_tail->next = NULL;
            new_tail->prev = old_tail;

            old_tail->next = new_tail;

            l->tail = new_tail;

            l->len++;
        }
    } else {
        perror("Failed to allocate memory");
        exit(1);
    }
}


int list_pop(List *l) {
    int pull;
    if (l->len == 0) { // if list is empty return 0
        pull = 0; // TODO: distinguish whether the list is empty or it has a 0 stored
    } else if (l->len == 1) { // if it has a single element
        Node *old_head = l->head;
        pull = old_head->value;

        l->head = NULL;
        l->tail = NULL;

        free(old_head);

        l->len--;
    } else { // it has multiple elements
        Node *old_head = l->head;
        Node *new_head = old_head->next;

        pull = old_head->value;

        l->head = new_head;
        l->head->prev = NULL;

        free(old_head);

        l->len--;
    }

    return pull;
}

int list_pop_back(List *l) {
    int pull;
    if (l->len == 0) { // if list is empty return 0
        pull = 0; // TODO: distinguish whether the list is empty or it has a 0 stored
    } else if (l->len == 1) { // if it has a single element
        Node *old_tail = l->tail;
        pull = old_tail->value;

        l->head = NULL;
        l->tail = NULL;

        free(old_tail);

        l->len--;
    } else { // it has multiple elements
        pull = l->tail->value;

        Node *old_tail = l->tail;
        Node *new_tail = old_tail->prev;


        l->tail = new_tail;
        l->tail->next = NULL;

        free(old_tail);

        l->len--;
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
