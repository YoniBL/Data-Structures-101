#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// Creates a node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Creates a list
struct List* createList() {
    struct List* newList = (struct List*)malloc(sizeof(struct List));
    if (newList == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newList->first = NULL;
    newList->last = NULL;
    newList->len = 0;
    return newList;
}

// Insert item to the end of a list
void append(struct List* lst, int data) {
    int curr_len = lst->len;
    struct Node* node = createNode(data);
    struct Node* curr_last;
    if (curr_len > 0) {
        curr_last = lst->last;
        curr_last->next = node;
    } else {
        lst->first = node;
    }
    lst->last = node;
    lst->len = curr_len + 1;
}

// Insert item by index
void insert(struct List* lst, int data, int index) {
    int len = lst->len;
    if (index < 0 || index > len) {
        printf("Invalid index\n");
        return;
    }
    if (len == 0 || index == len) {
        append(lst, data);
        return;
    }
    struct Node* node = createNode(data);
    struct Node* curr;
    int i = 0;
    curr = lst->first;
    while (i < index - 1) {
        curr = curr->next;
        i++;
    }
    node->next = curr->next;
    curr->next = node;
    lst->len = len + 1;
}

// Get the length of the list
int getLength(struct List* lst) {
    return lst->len;
}

// Delete item by data
void delete(struct List* lst, int data) {
    struct Node* prev = NULL;
    struct Node* curr = lst->first;

    while (curr != NULL && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return;
    }

    if (prev == NULL) {
        lst->first = curr->next;
    } else {
        prev->next = curr->next;
    }
    if (curr == lst->last) {
        lst->last = prev;
    }

    free(curr);
    lst->len--;
}

// Delete item by index
void pop(struct List* lst, int index) {
    if (index >= lst->len || index < 0) {
        printf("Invalid index\n");
        return;
    }
    struct Node* prev = NULL;
    struct Node* curr = lst->first;
    int i = 0;

    while (i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (prev == NULL) {
        lst->first = curr->next;
    } else {
        prev->next = curr->next;
    }
    if (curr == lst->last) {
        lst->last = prev;
    }

    free(curr);
    lst->len--;
}

// Empty a list from its elements
void clear(struct List* lst) {
    struct Node* curr = lst->first;
    struct Node* next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    lst->first = NULL;
    lst->last = NULL;
    lst->len = 0;
}

// Delete a list
void deleteList(struct List* lst) {
    clear(lst);
    free(lst);
}

// Get element for a certain index
int retrieve(struct List* lst, int index) {
    if (lst->len <= index || index < 0) {
        printf("Invalid Index\n");
        return -1;
    }
    int i = 0;
    struct Node* curr = lst->first;
    while (i < index) {
        curr = curr->next;
        i++;
    }
    return curr->data;
}

// Search for an element in the list
int search(struct List* lst, int data) {
    struct Node* curr = lst->first;
    int i = 0;
    while (curr != NULL && curr->data != data) {
        curr = curr->next;
        i++;
    }
    if (curr == NULL) {
        return -1;
    }
    return i;
}

// Reverse a list
void reverse(struct List* lst) {
    if (lst->len == 0 || lst->len == 1) {
        return;
    }
    struct Node* prev = lst->first;
    struct Node* curr = prev->next;
    struct Node* next = curr->next;
    lst->last = lst->first;
    prev->next = NULL;
    while (next != NULL) {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;
    lst->first = curr;
}

// Concatenate two lists
void concate(struct List* l1, struct List* l2) {
    if (l1->last != NULL) {
        l1->last->next = l2->first;
    } else {
        l1->first = l2->first;
    }
    if (l2->last != NULL) {
        l1->last = l2->last;
    }
    l1->len += l2->len;
    l2->first = NULL;
    l2->last = NULL;
    l2->len = 0;
    free(l2);
}

// Get count of an element in the list
int count(struct List* lst, int element) {
    int cnt = 0;
    struct Node* curr = lst->first;
    while (curr != NULL) {
        if (curr->data == element) {
            cnt++;
        }
        curr = curr->next;
    }
    return cnt;
}
