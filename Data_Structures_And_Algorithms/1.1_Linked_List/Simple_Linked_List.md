# Simple Linked List

## Insertion Operation

Adding a new node in linked list is a more than one step activity. We shall learn this with diagrams here.

- __First__, create a node using the same structure and find the location where it has to be inserted.
  
  ![Simple Linked List insertion Diagram setp 1](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_insertion_0.jpg)
- __second__,Imagine that we are inserting a node B (NewNode), between A (LeftNode) and C (RightNode). Then point B.next to C.
  
  ![Simple Linked List insertion Diagram setp 2](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_insertion_1.jpg)
- __third__, the next node at the left should point to the new node.
  
  ![Simple Linked List insertion Diagram setp 3](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_insertion_2.jpg)
  
## Deletion Operation

Deletion is also a more than one step process. We shall learn with pictorial representation.

- __First__, locate the target node to be removed, by using searching algorithms.

  ![Simple Linked List Deletion Diagram setp 1](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_deletion_0.jpg)
- __Second__,The left (previous) node of the target node now should point to the next node of the target node.
  
  ![Simple Linked List Deletion Diagram setp 2](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_deletion_1.jpg)
- __Third__,we will remove what the target node is pointing at.
  
  ![Simple Linked List Deletion Diagram setp 3](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_deletion_2.jpg)

## Reverse Operation

We need to make the last node to be pointed by the head node and reverse the whole linked list.

- __First__, we traverse to the end of the list. It should be pointing to NULL. Now, we shall make it point to its previous node.
  
  ![Simple Linked List Reversion Diagram setp 1](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_reverse_1.jpg)
- __Second__,We have to make sure that the last node is not the last node. So we'll have some temp node, which looks like the head node pointing to the last node. Now, we shall make all left side nodes point to their previous nodes one by one.
  
  ![Simple Linked List Reversion Diagram setp 2](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_reverse_2.jpg)
- __Third__,Except the node (first node) pointed by the head node, all nodes should point to their predecessor, making them their new successor. The first node will point to NULL.
  
  ![Simple Linked List Reversion Diagram setp 3](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_reverse_3.jpg)
- __Fourth__,We'll make the head node point to the new first node by using the temp node.
  
  ![Simple Linked List Reversion Diagram setp 4](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_reverse_4.jpg)

| Operation                        | time Complexity |
| -------------------------------- | :-------------: |
| Traversion                       |      O(n)       |
| Insertion at Head                |      O(1)       |
| deletion at head                 |      O(1)       |
| Search                           |      O(n)       |
| finding Length                   |      O(n)       |
| insert at certain key            |      O(n)       |
| delete node of certain key       |      O(n)       |
| update node of a certain key     |      O(n)       |
| reverse a linked list            |      O(n)       |
| Sort by value      (bubble Sort) |     O(n^2)      |
