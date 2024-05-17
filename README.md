# Data Structures 101

Welcome to **Data Structures 101**! This project provides implementations of various fundamental data structures in different programming languages. Whether you're a beginner looking to understand the basics or an experienced developer needing reference implementations, this repository has something for you.

## Table of Contents

- [Introduction](#introduction)
- [Data Structures](#data-structures)
  - [Linked List (C)](#linked-list-c)
  - [Binary Search Tree (C)](#binary-search-tree-c)
  - [Hashset (C)](#hashset-c)
  - [Fibonacci Heap (Java)](#fibonacci-heap-java)
  - [AVL Tree (Python)](#avl-tree-python)
- [Contributing](#contributing)
- [License](#license)

## Introduction

**Data Structures 101** is a collection of data structure implementations in C, Java, and Python. Each implementation is designed to be simple and educational, making it easy to understand the core concepts of these data structures.

Understanding data structures is crucial for efficient algorithm design and problem-solving in computer science. This project covers a range of data structures, each with its own unique properties and use cases. The implementations are kept straightforward to facilitate learning and provide clear insights into how these data structures work under the hood.

## Data Structures

### Linked List (C)

A Linked List is a linear data structure where elements are stored in nodes, and each node points to the next node in the sequence. It is useful for applications that require dynamic memory allocation and efficient insertion and deletion operations.

**Features**:
- Dynamic size
- Efficient insertions/deletions
- Sequential access

- **Directory**: `C/LinkedList`
- **Source File**: `linked_list.c`

### Binary Search Tree (C)

A Binary Search Tree (BST) is a tree data structure where each node has at most two children, referred to as the left child and the right child. For each node, the left subtree contains only nodes with keys less than the node’s key, and the right subtree contains only nodes with keys greater than the node’s key. BSTs are used for efficient searching, insertion, and deletion operations.

**Features**:
- Logarithmic time complexity for search, insertion, and deletion
- In-order traversal results in sorted order of elements

- **Directory**: `C/BinarySearchTree`
- **Source File**: `binary_search_tree.c`

### Hashset (C)

A Hashset is a collection of unique elements that provides efficient insert, remove, and contains operations using a hash table. It is particularly useful when there is a need for fast membership checking.

**Features**:
- Constant time complexity for insert, remove, and contains operations
- No duplicate elements

- **Directory**: `C/Hashset`
- **Source File**: `hashset.c`

### Fibonacci Heap (Java)

A Fibonacci Heap is a priority queue data structure that supports a collection of operations such as insertion, finding the minimum, and union of two heaps. It is known for its efficient decrease-key and delete operations, making it suitable for algorithms like Dijkstra’s and Prim’s.

**Features**:
- Amortized constant time complexity for insertion and decrease-key operations
- Efficient minimum extraction and merging of heaps

- **Directory**: `Java/FibonacciHeap`
- **Source File**: `FibonacciHeap.java`

### AVL Tree (Python)

An AVL Tree is a self-balancing binary search tree where the difference in heights between the left and right subtrees of any node is at most one. This property ensures that the tree remains balanced, providing logarithmic time complexity for search, insertion, and deletion operations.

**Features**:
- Self-balancing with logarithmic height
- Efficient search, insertion, and deletion
- Guarantees O(log n) time complexity for operations

- **Directory**: `Python/AVLTree`
- **Source File**: `avl_tree.py`

## Contributing

We welcome contributions! If you find a bug or have an enhancement request, please open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
