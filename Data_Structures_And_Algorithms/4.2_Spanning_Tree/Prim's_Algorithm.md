# Prim's Spanning Tree Algorithm

Prim's algorithm to find minimum cost spanning tree (as Kruskal's algorithm) uses the greedy approach. Prim's algorithm shares a similarity with the shortest path first algorithms.

To contrast with Kruskal's algorithm and to understand Prim's algorithm better, we shall use the same example

![prime algorithms example](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_graph.jpg)

## **Step 1** - Remove all loops and parallel edges

![mst with loops](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_with_loops.jpg)

Remove all loops and parallel edges from the given graph. In case of parallel edges, keep the one which has the least cost associated and remove all others.

![mst without loops](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_without_loops.jpg)

## **Step 2** - Choose any arbitrary node as root node

In this case, we choose **S** node as the root node of Prim's spanning tree. This node is arbitrarily chosen, so any node can be the root node. One may wonder why any node can be a root node. So the answer is, in the spanning tree all the nodes of a graph are included and because it is connected then there must be at least one edge, which will join it to the rest of the tree.

## **Step 3** - Check outgoing edges and select the one with less cost

After choosing the root node S, we see that S,A and S,C are two edges with weight 7 and 8, respectively. We choose the edge S,A as it is lesser than the other.

![step 1](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_graph_step_1.jpg)

Now, the tree S-7-A is treated as one node and we check for all edges going out from it. We select the one which has the lowest cost and include it in the tree.

![step 2](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_graph_step_2.jpg)

After this step, S-7-A-3-C tree is formed. Now we'll again treat it as a node and will check all the edges again. However, we will choose only the least cost edge. In this case, C-3-D is the new edge, which is less than other edges' cost 8, 6, 4, etc.

![step 3](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_graph_step_3.jpg)

After adding node D to the spanning tree, we now have two edges going out of it having the same cost, i.e. D-2-T and D-2-B. Thus, we can add either one. But the next step will again yield edge 2 as the least cost. Hence, we are showing a spanning tree with both edges included.

![step 4](https://www.tutorialspoint.com/data_structures_algorithms/images/mst_prims_algorithm.jpg)

We may find that the output spanning tree of the same graph using two different algorithms is same.
