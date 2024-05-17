#include <stdio.h>
#include <stdlib.h>


// Creating a struct for the Node object
struct Node{
    int data;
    struct Node* next;
}Node;
// Creating a struct for the List object
struct List{
    struct Node* first;
    struct Node* last;
    int len;
}List;

/// Creates a node
struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

// Creates a list
struct List* createList(){
    struct List* newList = (struct List*)malloc(sizeof(struct List));
    if (newList == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    newList -> first = NULL;
    newList -> last = NULL;
    newList -> len = 0;
    return newList;
}

// Insert item to the end of a list
void append(struct List* lst, int data){
    int curr_len = lst -> len;
    struct Node* node = createNode(data);
    struct Node* curr_last;
    if (curr_len > 0){
        curr_last = lst -> last;
        curr_last -> next = node;
    }
    else {
        lst -> first = node;
    }
    lst -> last = node;
    lst -> len = curr_len + 1; 

}
// Insert item by index
void insert(struct List* lst, int data, int index){
    int len = lst -> len;
    if (index < 0 || index > len) {
        printf("Invalid index\n");
        return;
    }
    if (len == 0 || index == len ){
        append(lst, data);
        return;
    }
    struct Node* node = createNode(data);
    struct Node* curr;
    int i = 0;
    curr = lst -> first;
    while (i < index - 1){
        curr = curr -> next;
        i = i + 1;
    }
    node -> next = curr -> next;
    curr -> next = node;
    lst -> len = len + 1;
}

int getLength(struct List* lst){
    return lst -> len;
}

// Delete item by data
void delete(struct List* lst, int data){
    struct Node* prev = NULL;
    struct Node* curr = lst->first;

    // Traverse the list to find the node with the specified data
    while (curr != NULL && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    // If the node is not found, do nothing
    if (curr == NULL) {
        return;
    }

    // Update pointers to remove the node from the list
    if (prev == NULL) {
        lst->first = curr->next; // Update the first pointer if the node to delete is the first node
    } else {
        prev->next = curr->next;
    }
    if (curr == lst->last) {
        lst->last = prev; // Update the last pointer if the node to delete is the last node
    }

    // Free the memory allocated for the deleted node
    free(curr);

    // Update the length of the list
    lst->len--;
}

// Delete item by index
void pop(struct List* lst, int index){
    // Check if index is valid
    if (index >= lst -> len || index < 0){
        printf("Invalid index\n");
        return;
    }
    struct Node* prev = NULL;
    struct Node* curr = lst->first;
    int i = 0;

    // Traverse the list to find the node with the correct index
    while (i < index) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    // Update pointers to remove the node from the list
    if (prev == NULL) {
        lst->first = curr->next; // Update the first pointer if the node to delete is the first node
    } else {
        prev->next = curr->next;
    }
    if (curr == lst->last) {
        lst->last = prev; // Update the last pointer if the node to delete is the last node
    }

    // Free the memory allocated for the deleted node
    free(curr);

    // Update the length of the list
    lst->len--;
}

// Empty a list from it's elements
void clear(struct List* lst){
    struct Node* curr;
    struct Node* next;
    curr = lst -> first;
    next = curr -> next;
    lst -> first = NULL;
    while (next != lst -> last){
        curr -> next = NULL;
        free(curr);
        curr = next;
        next = next -> next;
    }
    lst -> last = NULL;
    curr -> next = NULL;
    free(curr);
    free(next);
    lst -> len = 0;
}

// Delete a list 
void deleteList(struct List* lst){
    clear(lst);
    free(lst);
}

// Get element for a certain index
int retrieve(struct List* lst, int index){
    if (lst -> len <= index || index < 0){
        printf("Invalid Index\n");
        return -1;
    }
    int i = 0;
    struct Node* curr = lst -> first;
    while (i < index){
        curr = curr -> next;
        i++;
    }
    return curr -> data;
}

int search(struct List* lst, int data){
    struct Node* curr;
    int i;
    if (lst == NULL){
        return -1;
    }
    curr = lst -> first;
    i = 0;
    while (curr != NULL && curr -> data != data){
        curr = curr -> next;
        i++;
    }
    if (curr == NULL){
        return -1;
    }
    return i;
}

// Reverse a list
void reverse(struct List* lst){
    if (lst -> len == 0 || lst -> len == 1){
        return;
    }
    if (lst -> len == 2){
        struct Node* newfirst = lst -> last;
        struct Node* newlast = lst -> first;
        lst -> first = newlast;
        lst -> last = newfirst;
        lst -> first -> next = lst -> last;
        lst -> last -> next = NULL;
        return;
    }
    struct Node* prev = lst -> first;
    struct Node* curr = prev -> next;
    struct Node* nxt = curr -> next;
    lst -> last = lst -> first;
    prev -> next = NULL;
    while (nxt != NULL){
        curr -> next = prev;
        prev = curr;
        curr = nxt;
        nxt = nxt -> next;
    }
    curr -> next = prev;
    lst -> first = curr;
}

// Concate two lists.
//@pre : l1, l2 are two different lists
//@post : l1 = l2 merged into the end of l1, l2 is empty
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
    l2-> first = NULL;
    l2 -> last = NULL;
    l2 -> len = 0;
    free(l2);
}


// Gets #element in list 
int count(struct List* lst, int element){
    int cnt = 0;
    struct Node* curr = lst -> first;
    while (curr != NULL){
        if (curr -> data == element){
            cnt++;
        }
        curr = curr -> next;
    }
    return cnt;
}

/// SMALL TESTS 
void testLinkedList() {
    // Create a new list
    struct List* lst = createList();
    // Insert elements into the list
    insert(lst, 10, 0);
    insert(lst, 20, 1);
    insert(lst, 30, 2);

    // Test clear function
    printf("Testing clear function...\n");
    clear(lst);
    if (lst -> first == NULL && lst ->last == NULL && lst ->len == 0) {
        printf("Clear function test passed\n");
    } else {
        printf("Clear function test failed\n");
    }

    // Insert elements into the list again
    insert(lst, 10, 0);
    insert(lst, 20, 1);
    insert(lst, 30, 2);

    // Test retrieve function
    printf("\nTesting retrieve function...\n");
    printf("Element at index 0: %d\n", retrieve(lst, 0)); // Expected output: 10
    printf("Element at index 1: %d\n", retrieve(lst, 1)); // Expected output: 20
    printf("Element at index 2: %d\n", retrieve(lst, 2)); // Expected output: 30
    printf("Element at index 3: %d\n", retrieve(lst, 3)); // Expected output: Invalid index

    // Test reverse function
    printf("\nTesting reverse function...\n");
    reverse(lst);
    printf("Reversed list:\n");
    for (struct Node* curr = lst->first; curr != NULL; curr = curr->next) {
        printf("%d ", curr->data);
    }
    printf("\n");

    // Create a second list
    struct List* lst2 = (struct List*)malloc(sizeof(struct List));
    insert(lst2, 40, 0);
    insert(lst2, 50, 1);
    insert(lst2, 60, 2);

    // Test concate function
    printf("\nTesting concate function...\n");
    concate(lst, lst2);
    printf("Combined list:\n");
    for (struct Node* curr = (lst->first); curr != NULL; curr = curr->next) {
        printf("%d ", curr->data);
    }
    printf("\n");

    // Test count function
    printf("\nTesting count function...\n");
    printf("Count of 20 in list: %d\n", count(lst, 20)); // Expected output: 1
    printf("Count of 30 in list: %d\n", count(lst, 30)); // Expected output: 1
    printf("Count of 40 in list: %d\n", count(lst, 40)); // Expected output: 1
    printf("Count of 70 in list: %d\n", count(lst, 70)); // Expected output: 0

    // Free memory for combined list
    deleteList(lst);
}


int main() {
    // Run the test function
    testLinkedList();

    return 0;
}