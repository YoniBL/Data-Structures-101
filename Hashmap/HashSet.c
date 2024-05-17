#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <stdbool.h>

typedef struct Hashset {
    struct List* array[1000];
} Set;

Set* createSet();
void addItem(Set* s, int element);
void deleteItem(Set* s, int element);
bool find(Set* s, int element);
void deleteSet(Set* s);

Set* createSet() {
    Set* s = (Set*)malloc(sizeof(Set));
    if (s == NULL) {
        return NULL;
    }
    for (int i = 0; i < 1000; i++) {
        s->array[i] = NULL;
    }
    return s;
}

void addItem(Set* s, int element) {
    int location = element % 1000;
    struct List* lst = s->array[location];
    if (find(s, element)) {
        return;
    }
    if (lst == NULL) {
        lst = createList();
        s->array[location] = lst;
    }
    append(lst, element);
}

void deleteItem(Set* s, int element) {
    int location = element % 1000;
    struct List* lst = s->array[location];
    if (lst != NULL) {
        delete(lst, element);
    }
}

bool find(Set* s, int element) {
    int location = element % 1000;
    struct List* lst = s->array[location];
    if (lst == NULL) {
        return false;
    }
    return search(lst, element) != -1;
}

void deleteSet(Set* s) {
    for (int i = 0; i < 1000; i++) {
        if (s->array[i] != NULL) {
            deleteList(s->array[i]);
        }
    }
    free(s);
}

void testHashSet() {
    Set* s = createSet();
    bool test1, test11, test111;

    // Add elements to the set
    for (int i = 0; i < 500; i++) {
        addItem(s, i);
        addItem(s, 1000 + i);
        addItem(s, 10000 + i);
    }

    // Test if elements are found
    for (int i = 0; i < 500; i++) {
        test1 = find(s, i);
        test11 = find(s, 1000 + i);
        test111 = find(s, 10000 + i);
        if (!test1 || !test11 || !test111) {
            printf("Test 1 failed\n");
            printf("Element in set not found\n");
            if (!test1) {
                printf("%d not in set ", i);
            }
            return;
        }
    }

    // Test if elements not in the set are found
    for (int i = 500; i < 1000; i++) {
        test1 = find(s, i);
        if (test1) {
            printf("Test 2 failed\n");
            printf("Element not in set found");
            return;
        }
    }

    // Delete some elements and test again
    for (int i = 0; i < 500; i += 2) {
        deleteItem(s, i);
    }

    for (int i = 0; i < 500; i += 2) {
        test1 = find(s, i);
        test11 = find(s, i + 1);
        if (test1 || !test11) {
            printf("Test 3 failed\n");
            printf("Error in deletion\n");
            return;
        }
    }

    deleteSet(s);
    printf("All tests passed!\n");
}

int main() {
    // Run the test function
    testHashSet();

    return 0;
}
