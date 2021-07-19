# Depth-First-Search

Depth First Search (DFS) algorithm traverses a graph in a depthward motion and uses a stack to remember to get the next vertex to start a search, when a dead end occurs in any iteration.

![DFS Traversal](https://www.tutorialspoint.com/data_structures_algorithms/images/depth_first_traversal.jpg)

As in the example given above, DFS algorithm traverses from S to A to D to G to E to B first, then to F and lastly to C. It employs the following rules.

- **Rule 1** − Visit the adjacent unvisited vertex. Mark it as visited. Display it. Push it in a stack.

- **Rule 2** − If no adjacent vertex is found, pop up a vertex from the stack. (It will pop up all the vertices from the stack, which do not have adjacent vertices.)

- **Rule 3** − Repeat Rule 1 and Rule 2 until the stack is empty.

| Step |                                          Traversal                                           |                                                                                                                                                                                                  Description |
| ---- | :------------------------------------------------------------------------------------------: | -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| 1    |   ![dfs_one](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_one.jpg)   |                                                                                                                                                                                        Initialize the stack. |
| 2    |   ![dfs_tow](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_two.jpg)   | Mark S as visited and put it onto the stack. Explore any unvisited adjacent node from S. We have three nodes and we can pick any of them. For this example, we shall take the node in an alphabetical order. |
| 3    | ![dfs_three](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_three.jpg) |                                       Mark A as visited and put it onto the stack. Explore any unvisited adjacent node from A. Both S and D are adjacent to A but we are concerned for unvisited nodes only. |
| 4    |  ![dfs_four](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_four.jpg)  |                 Visit D and mark it as visited and put onto the stack. Here, we have B and C nodes, which are adjacent to D and both are unvisited. However, we shall again choose in an alphabetical order. |
| 5    |  ![dfs_five](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_five.jpg)  |                                                                       We choose B, mark it as visited and put onto the stack. Here B does not have any unvisited adjacent node. So, we pop B from the stack. |
| 6    |   ![dfs_six](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_six.jpg)   |                                                               We check the stack top for return to the previous node and check if it has any unvisited nodes. Here, we find D to be on the top of the stack. |
| 7    | ![dfs_seven](https://www.tutorialspoint.com/data_structures_algorithms/images/dfs_seven.jpg) |                                                                                                Only unvisited adjacent node is from D is C now. So we visit C, mark it as visited and put it onto the stack. |

As C does not have any unvisited adjacent node so we keep popping the stack until we find a node that has an unvisited adjacent node. In this case, there's none and we keep popping until the stack is empty.
