# Stack

A stack is an Abstract Data Type (ADT), commonly used in most programming languages. It is named stack as it behaves like a real-world stack, for example – a deck of cards or a pile of plates

A stack can be implemented by means of Array, Structure, Pointer, and Linked List. Stack can either be a fixed size one or it may have a sense of dynamic resizing. Here, we are going to implement stack using arrays, which makes it a fixed size stack implementation.

## Basic Operations

Stack operations may involve initializing the stack, using it and then de-initializing it. Apart from these basic stuffs, a stack is used for the following two primary operations −

- __push()__ − Pushing (storing) an element on the stack.

- __pop()__ − Removing (accessing) an element from the stack.

When data is PUSHed onto stack.

To use a stack efficiently, we need to check the status of stack as well. For the same purpose, the following functionality is added to stacks −

- __peek()__ − get the top data element of the stack, without removing it.

- __isFull()__ − check if stack is full.

- __isEmpty()__ − check if stack is empty.

At all times, we maintain a pointer to the last PUSHed data on the stack. As this pointer always represents the top of the stack, hence named top. The top pointer provides top value of the stack without actually removing it.

### Push Operation

The process of putting a new data element onto stack is known as a Push Operation. Push operation involves a series of steps −

- __Step 1__ − Checks if the stack is full.

- __Step 2__ − If the stack is full, produces an error and exit.

- __Step 3__ − If the stack is not full, increments top to point next empty space.

- __Step 4__ − Adds data element to the stack location, where top is pointing.

- __Step 5__ − Returns success.

![Push Operation UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/stack_push_operation.jpg)

### Pop Operation

A Pop operation may involve the following steps −

- __Step 1__ − Checks if the stack is empty.

- __Step 2__ − If the stack is empty, produces an error and exit.

- __Step 3__ − If the stack is not empty, accesses the data element at which top is pointing.

- __Step 4__ − Decreases the value of top by 1.

- __Step 5__ − Returns success.

![POP operation UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/stack_pop_operation.jpg)
