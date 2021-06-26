# Queue

a __queue__ is open at both its ends. One end is always used to insert data (enqueue) and the other is used to remove data (__dequeue__). Queue follows **First-In-First-Out** methodology.

A real-world example of queue can be a single-lane one-way road, where the vehicle enters first, exits first. More real-world examples can be seen as queues at the ticket windows and bus-stops.

As in stacks, a queue can also be **implemented** using ___Arrays___, ___Linked-lists___, ___Pointers___ and ___Structures___. For the sake of simplicity, we shall implement queues using one-dimensional array.

## Basic Operations

- __enqueue()__ − add (store) an item to the queue.
- __dequeue()__ − remove (access) an item from the queue.

Few more functions are required to make the above-mentioned queue operation efficient. These are −>

- __peek()__ − Gets the element at the front of the queue without removing it.
- __isfull()__ − Checks if the queue is full.
- __isempty()__ − Checks if the queue is empty.
