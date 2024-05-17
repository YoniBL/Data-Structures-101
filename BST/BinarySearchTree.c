#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct BinarySearchTree
{
    Node* root;
    Node* min;
    Node* max;
    int size;

}bst;


Node* createNode(int data){
    Node* res = (Node*)malloc(sizeof(Node));
    if (res == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    res -> data = data;
    res -> left = NULL;
    res -> right = NULL;
    res -> parent = NULL;
    return res;
}

bst* createTree(){
    bst* tree = (bst*)malloc(sizeof(bst));
    if (tree == NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    tree -> root = NULL;
    tree -> max = NULL;
    tree -> min = NULL;
    tree -> size = 0;
    return tree;
}


void insertElement(bst* tree, Node* tree_node, Node* element){
    if (tree_node -> data < element -> data){
        if (tree_node -> right == NULL){
            tree_node -> right = element;
            element -> parent = tree_node;
            if (tree -> max == tree_node){
                tree -> max = element;
            }
            return;
        }
    else{
        insertElement(tree, tree_node -> right, element);
        }
    }
    if (tree_node -> data > element -> data){
        if (tree_node -> left == NULL){
            tree_node -> left = element;
            element -> parent = tree_node;
            if (tree -> min == tree_node){
                tree -> min = element;
            }
            return;
        }
        else{
            insertElement(tree, tree_node -> left, element);
            }
        }
    else{
        return;
    }   
}

Node* successor(bst* tree, Node* node){
    Node* res;
    Node* curr;
    if (tree -> max == node){
        return NULL;
    }
    // If node has a right child, his succ is the leftmost son of his right child
    if (node -> right != NULL){
        res = node -> right;
        while (res -> left != NULL){
            res = res -> left;
        }
        return res;
    }
    // otherwise, "go up untill we turn right" 
    res = node -> parent;
    curr = node;
    while (res -> right == curr){
        curr = res; 
        res = res -> parent;
    }
    return res; 
}

void insert(int data, bst* tree){
    Node* elem = createNode(data);
    if (tree -> size == 0){
        tree -> root = elem;
        tree -> max = elem;
        tree -> min = elem;
        tree -> size ++;
    }
    else{
        insertElement(tree, tree -> root, elem);
        tree -> size++;
    }
}


// retrieve data of i'th element
int retrieve(bst* tree, int index){
    if (index >= tree -> size) {
        printf("Invalid index\n");
        return -1;
    }
    Node* curr = tree -> min;
    int i = 0;
    while (i < index){
        curr = successor(tree, curr);
        i++;
    }
    return curr -> data;
}

void deleteNode(bst* tree, int data){
    Node* curr;
    Node* par;
    Node* suc;
    Node* suc_parent;
    curr = tree -> root;
    // Look for element with data as data
    while (curr != NULL && curr -> data != data){
        if (curr -> data > data){
            curr = curr -> left;
        }
        else{
            curr = curr -> right;
        }
    }
    // If no such element, do nothing
    if (curr == NULL){
        return;
    }
    // If curr is a node s.t. curr.data = data
    else{
        par = curr -> parent;
        // node to delete is a leaf
        if (curr -> left == NULL && curr -> right == NULL){
            if (tree -> max == curr || tree -> min == curr){
                if (tree -> max == curr){
                    tree -> max = par;
                }
                else{
                    tree -> min = par;
                }
            }
            curr -> parent = NULL;
            if (par -> right == curr){
                par -> right = NULL;
            }
            else{
                par -> left = NULL;
            }
            curr -> parent = NULL;
            free(curr);
            tree -> size --;
            return;
        }
        else{
            // node to delete has one child
            if (curr -> left == NULL || curr -> right == NULL){
                if (curr -> left == NULL){ // curr has one right child
                    if (curr == par -> right){ // curr is a right child of par
                        par -> right = curr -> right;
                    }
                    else{ // curr is a left child of par 
                        par -> left = curr -> right;
                    }
                    curr ->right = NULL;
                    curr -> parent = NULL;
                    free(curr);
                    tree -> size --;
                    return;
                }
                else{ // curr has one left child
                    if (curr == par -> right){
                        par -> right = curr -> left;
                    }
                    else{
                        par -> left = curr -> left;
                    }
                    curr -> left = NULL;
                    curr -> parent = NULL;
                    free(curr);
                    tree -> size --;
                    return;
                }
            }
            else{ // curr has two children
                suc = successor(tree, curr);
                if (suc == tree -> max){
                    tree -> max = suc -> parent;
                }
                suc_parent = suc -> parent;
                curr -> data = suc -> data;
                if (suc_parent -> left == suc){
                    suc_parent -> left = NULL;
                }
                else{
                    suc_parent -> right = NULL;
                }
                suc ->parent = NULL;
                free(suc);
                tree -> size --;
                return;
            }
        }
    }
}

void delete(bst* tree, int data){
    if (tree -> size == 0) {
        return; 
    }
    if (tree -> size == 1){
        if (tree -> root -> data == data){
            Node* curr;
            curr = tree -> root;
            tree -> root = NULL;
            tree -> max = NULL;
            tree -> min = NULL;
            tree -> size --;
            free(curr);
        }
    }
    else{
        deleteNode(tree, data);
    }

}

Node* getMax(bst* tree){
    if (tree -> size != 0){
        return tree -> max;
    }
    else{
        printf("Error retrieving Max, Tree is empty\n");
        exit(0);
    }
}

Node* getMin(bst* tree){
    if (tree -> size != 0){
        return tree -> min;
    }
    else{
        printf("Error retrieving Min, Tree is empty\n");
        exit(0);
    }
}

#include <stdio.h>
#include <assert.h>

int main() {
    // Create a new BST
    bst* tree = createTree();

    // Test insertion
    insert(5, tree);
    insert(3, tree);
    insert(7, tree);
    insert(1, tree);
    insert(4, tree);
    insert(6, tree);
    insert(9, tree);

    // Test retrieval
    assert(retrieve(tree, 0) == 1); // 1st smallest element
    assert(retrieve(tree, 3) == 5); // 4th smallest element
    assert(retrieve(tree, 6) == 9); // Largest element

    // Test deletion
    delete(tree, 7); // Delete node with value 7
    assert(retrieve(tree, 4) == 6); // New largest element
    assert(retrieve(tree, 6) == -1); // Deleted element no longer exists

    // Test deletion of root
    delete(tree, 5); // Delete root node
    assert(retrieve(tree, 0) == 1); // New root
    assert(retrieve(tree, 3) == 6); // Check if BST is still valid

    // Test deletion of non-existent element
    delete(tree, 10); // Deleting non-existent element should have no effect
    assert(retrieve(tree, 4) == 9);
    // Test deletion of all elements
    delete(tree, 1);
    delete(tree, 3);
    delete(tree, 4);
    delete(tree, 6);
    delete(tree, 9);
    assert(tree->size == 0); // Tree should be empty after deleting all elements

    printf("All tests passed successfully!\n");

    // Free memory
    free(tree);

    return 0;
}






