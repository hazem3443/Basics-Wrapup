# link List

A linked list is a sequence of data structures, which are connected together via links.

## Linked List Representation

Linked list can be visualized as a chain of nodes, where every node points to the next node.

## Types of Linked List

- [__Simple Linked List__](Simple_Linked_List.md) −> Item navigation is forward only.
![Simple Linked List UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list.jpg)

- [__Doubly Linked List__](Doubly_Linked_List.md) −> Items can be navigated forward and backward.
![Boubly Linked List UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/doubly_linked_list.jpg)

- [__Circular Linked List__](Circular_Linked_List.md) −> Last item contains link of the first element as next and the first element has a link to the last element as previous.
![Circular Linked List UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/singly_circular_linked_list.jpg)

## Basic Operations

Following are the basic operations supported by a list.

- __Insertion__ − Adds an element at the beginning of the list.
- __Deletion__ − Deletes an element at the beginning of the list.
- __Display__ − Displays the complete list.
- __Search__ − Searches an element using the given key.
- __Delete__ − Deletes an element using the given key.

## Applications of linked list in real world-

1. __Image viewer__ – Previous and next images are linked, hence can be accessed by next and previous button.
2. __Previous and next page in web browser__ – We can access previous and next url searched in web browser by pressing back and next button since, they are linked as linked list.
3. __Music Player__ – Songs in music player are linked to previous and next song. you can play songs either from starting or ending of the list.

## Applications of Circular Linked Lists

-Circular lists are useful in applications to repeatedly go around the list. For example, when multiple applications are running on a PC, it is common for the operating system to put the running applications on a list and then to cycle through them, giving each of them a slice of time to execute, and then making them wait while the CPU is given to another application. It is convenient for the operating system to use a circular list so that when it reaches the end of the list it can cycle around to the front of the list.

- Circular Doubly Linked Lists are used for implementation of advanced data structures like __Fibonacci Heap__.
