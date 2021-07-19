# Breadth-First Search

Breadth First Search (BFS) algorithm traverses a graph in a breadthward motion and uses a queue to remember to get the next vertex to start a search, when a dead end occurs in any iteration.

![Breadth-First-Search](https://www.tutorialspoint.com/data_structures_algorithms/images/breadth_first_traversal.jpg)

As in the example given above, BFS algorithm traverses from A to B to E to F first then to C and G lastly to D. It employs the following rules.

- **Rule 1** − Visit the adjacent unvisited vertex. Mark it as visited. Display it. Insert it in a queue.

- **Rule 2** − If no adjacent vertex is found, remove the first vertex from the queue.

- **Rule 3** − Repeat Rule 1 and Rule 2 until the queue is empty.

| Step |                                          Traversal                                           |                                                                                                                                            Description |
| ---- | :------------------------------------------------------------------------------------------: | -----------------------------------------------------------------------------------------------------------------------------------------------------: |
| 1    |   ![bfs_one](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_one.jpg)   |                                                                                                                                  Initialize the queue. |
| 2    |   ![bfs_tow](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_two.jpg)   |                                                                                      We start from visiting S (starting node), and mark it as visited. |
| 3    | ![bfs_three](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_three.jpg) | We then see an unvisited adjacent node from S. In this example, we have three nodes but alphabetically we choose A, mark it as visited and enqueue it. |
| 4    |  ![bfs_four](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_four.jpg)  |                                                                   Next, the unvisited adjacent node from S is B. We mark it as visited and enqueue it. |
| 5    |  ![bfs_five](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_five.jpg)  |                                                                   Next, the unvisited adjacent node from S is C. We mark it as visited and enqueue it. |
| 6    |   ![bfs_six](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_six.jpg)   |                                                                            Now, S is left with no unvisited adjacent nodes. So, we dequeue and find A. |
| 7    | ![bfs_seven](https://www.tutorialspoint.com/data_structures_algorithms/images/bfs_seven.jpg) |                                                                     From A we have D as unvisited adjacent node. We mark it as visited and enqueue it. |

At this stage, we are left with no unmarked (unvisited) nodes. But as per the algorithm we keep on dequeuing in order to get all unvisited nodes. When the queue gets emptied, the program is over.

the only difference i noticed between DFS & BFS is that

- DFS uses Stack
- BFS uses Queue  
and all functions stay the same and the Breadth & depth traversal algorithms stay the same.
