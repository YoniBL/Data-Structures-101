#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* first;
    struct Node* last;
    int len;
};

struct List* createList();
void append(struct List* lst, int element);
void delete(struct List* lst, int element);
int search(struct List* lst, int element);
void deleteList(struct List* lst);

#endif // LINKED_LIST_H
