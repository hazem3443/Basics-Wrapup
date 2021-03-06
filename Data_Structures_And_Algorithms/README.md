# Data Structures - Algorithms Basics

The data in the data structures are processed by certain operations. The particular data structure chosen largely __depends on__ the frequency of the operation that needs to be performed on the data structure.

- Traversing
- Searching
- Insertion
- Deletion
- Sorting
- Merging

- ## Data Structures
  
  - [Arrays](1.0_Arrays)
  - [Linked List](1.1_Linked_List)
  - [Stack](1.2_Stack)
  - [Queue](1.3_Queue)

- ## Algorithms

  - ### Searching

    - [Linear Search](2.1.0_Linear_Search)
    - [Binary Search](2.1.1_Binary_Search)
    - [interpolation Search](2.1.2_Interpolation_Search)
    - [Hash Table](2.1.3_Hash_Table)
  
  - ### Sorting
  
    - [Bubble Sort](2.2.0_Bubble_Sort)
    - [Insertion Sort](2.2.1_Insertion_Sort)
    - [Selection Sort](2.2.2_Selection_Sort)
    - [Merge Sort](2.2.3_Merge_Sort)
    - [Shell Sort](2.2.4_Shell_Sort)
    - [Quick Sort](2.2.5_Quick_Sort)

- ## Graph

  - [Depth First Traversal](3.0_DFT)
  - [Breadth First Traversal](3.1_BFT)

- ## Tree

  - [Binary Search Tree](4.0_Binary_Search_Tree)
  - [AVL Tree](4.1_AVL_Tree)
  - [Spanning Tree](4.2_Spanning_Tree)
  - [Heap](4.3_Heap)
  
- ## Recursion

  - [Tower of Hanoi](5.0_Tower_Of_Hanoi)
  - [Fibonacci Series](5.1_Fibonacci_Series)

### for more productivity

we can add __gccAutomationScript.sh__ bash script file to command line aliases in __.bashrc__ file

```bash
~$vim ~/.bashrc 
```

and add this line

```sh
alias runc='~/Desktop/basics/Data_Structures_And_Algorithms/gccAutomationScript.sh'
```

then source .bashrc file

```bash
~$source ~/.bashrc
```

now you can use __runc__ command to run .c files such that

```bash
~$runc test.c
```
