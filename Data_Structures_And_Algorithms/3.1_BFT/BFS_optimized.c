/*
the only difference i noticed between DFS & BFS is that 
-- DFS uses Stack
-- BFS uses Queue
and all functions stay the same and the Breadth & depth traversal algorithms stay the same.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct
{
    char queue[MAX];
    int rear;
    int front;
    int queueItemCount;
} Queue_type;

//Stack functions
void Queue(Queue_type *queue, char val);
char Dequeue(Queue_type *queue);
bool IsEmpty(Queue_type *queue);
/*
//adjacent matrix for each vertex
//example suppose we have S A B C D Graphics
/*
                S
              / | \
             A  B  C
              \ | /
                D
*/
//then this matrix will be look like this
//  S A B C D
//S 0 1 1 1 0
//A 1 0 0 0 1
//B 1 0 0 0 1
//C 1 0 0 0 1
//D 0 1 1 1 0

typedef struct
{
    char label;
    bool visited;
} Vertex_type;

typedef struct
{
    Vertex_type *List_Vertices[MAX];
    int vertexCount;
    bool adjMatrix[MAX][MAX];

} Graph_type;

Vertex_type *List_Vertices[MAX];
Graph_type Graph1 = {{0}, 0, {0}};

// bool adjMatrix[MAX][MAX];

//Graph Operations
void AddVertex(Graph_type *graph, char label);
void addEdge(Graph_type *graph, int start, int end);

//Depth-First-Search Operations
int getAdjUnvisitedVertex(Graph_type *graph, int vertexIndex);
void displayVertex(Graph_type *graph, int vertexIndex);
int BreadthFirstSearch(Graph_type *graph, char val);

void main()
{
    AddVertex(&Graph1, 'S'); // 0
    AddVertex(&Graph1, 'A'); // 1
    AddVertex(&Graph1, 'B'); // 2
    AddVertex(&Graph1, 'C'); // 3
    AddVertex(&Graph1, 'D'); // 4

    addEdge(&Graph1, 0, 1); // S - A
    addEdge(&Graph1, 0, 2); // S - B
    addEdge(&Graph1, 0, 3); // S - C
    addEdge(&Graph1, 1, 4); // A - D
    addEdge(&Graph1, 2, 4); // B - D
    addEdge(&Graph1, 3, 4); // C - D

    printf("Depth First Search: ");
    printf("\n vertex_index = %i\n", BreadthFirstSearch(&Graph1, 'Z'));

    /*
    Queue_type Queue1 = {{0}, -1, 0, 0};

    Queue(&Queue1, 'S');
    Queue(&Queue1, 'A');
    Queue(&Queue1, 'B');
    Queue(&Queue1, 'C');
    Queue(&Queue1, 'D');

    printf("Stack pop = %c\n", Dequeue(&Queue1));
    printf("Stack pop = %c\n", Dequeue(&Queue1));
    printf("Stack pop = %c\n", Dequeue(&Queue1));
    printf("Stack pop = %c\n", Dequeue(&Queue1));
    printf("Stack pop = %c\n", Dequeue(&Queue1));

    printf("Queue Rear = %i, Queue Front = %i, Queue size = %i\n", Queue1.rear, Queue1.front, Queue1.queueItemCount);

    printf("Stack pop = %c\n", Dequeue(&Queue1));
    printf("Stack pop = %c\n", Dequeue(&Queue1));

    printf("Queue Rear = %i, Queue Front = %i, Queue Size = %i\n", Queue1.rear, Queue1.front, Queue1.queueItemCount);
    Queue(&Queue1, 'C');
    Queue(&Queue1, 'D');

    printf("IsEmpty = %i\n", IsEmpty(&Queue1));
    */
}
//Graph Functions--------------------------------------------------------

void AddVertex(Graph_type *graph, char label)
{
    Vertex_type *vertex = (Vertex_type *)malloc(sizeof(Vertex_type));
    vertex->label = label;
    vertex->visited = false;

    //Graph list will contain all vertices
    graph->List_Vertices[graph->vertexCount++] = vertex;
    // lstVertices[vertexCount++] = vertex; //add vertex to list of vertices list
}

void addEdge(Graph_type *graph, int start, int end)
{
    //for undirected vertex merk to and from as connected vertices
    graph->adjMatrix[start][end] = 1;
    graph->adjMatrix[end][start] = 1;
}

//Queue Functions--------------------------------------------------------
void Queue(Queue_type *queue, char val)
{
    if (queue->queueItemCount != MAX) //if not full then insert data
    {
        if (queue->rear == MAX - 1) //if
            queue->rear = -1;
        queue->queue[++queue->rear] = val;
        queue->queueItemCount++;
    }
    //else do nothing which means it won't be inserted in the queue
}

char Dequeue(Queue_type *queue)
{
    if (queue->queueItemCount != 0) //if not empty remove data
    {
        int data = queue->queue[queue->front++];

        if (queue->front == MAX)
            queue->front = 0;

        queue->queueItemCount--;
        return data;
    }
    //else do nothing
}

bool IsEmpty(Queue_type *queue)
{
    return queue->queueItemCount == 0;
}

//Depth-First-Search Functions------------------------------
int getAdjUnvisitedVertex(Graph_type *graph, int vertexIndex)
{
    int i;

    for (i = 0; i < graph->vertexCount; i++)
    {
        if (graph->adjMatrix[vertexIndex][i] == 1 && graph->List_Vertices[i]->visited == false)
        {
            return i; //index of vertex in adjacent list = index in vertices list = i
        }
    }

    return -1; //no adjacent unvisited vertices
}

void displayVertex(Graph_type *graph, int vertexIndex)
{
    printf("%c ", graph->List_Vertices[vertexIndex]->label);
}
//this function will traverse the Graph
int BreadthFirstSearch(Graph_type *graph, char val)
{
    int i;
    Queue_type Queue1 = {{0}, -1, 0, 0}; //create the stack for vertices traversal

    //mark first node as visited
    graph->List_Vertices[0]->visited = true;

    //display the vertex at index 0
    displayVertex(graph, 0);

    //push vertex index in stack
    Queue(&Queue1, 0);

    //check condition for first vertex
    if (graph->List_Vertices[0]->label == val)
    {
        for (i = 0; i < graph->vertexCount; i++)
        {
            graph->List_Vertices[i]->visited = false;
        }
        return 0;
    }

    while (!IsEmpty(&Queue1))
    {
        //get the unvisited vertex of vertex which is at top of the stack
        int unvisitedVertex_index = getAdjUnvisitedVertex(graph, (Queue1.queue[Queue1.front])); //returns index of unvisited vertex

        //no adjacent vertex found
        if (unvisitedVertex_index == -1)
            Dequeue(&Queue1);
        else
        {
            graph->List_Vertices[unvisitedVertex_index]->visited = true; //mark this vertex as visited
            displayVertex(graph, unvisitedVertex_index);                 //display the vertex
            Queue(&Queue1, unvisitedVertex_index);                       //push it to the stack
            //to seach for certain vertex you can puth the check here with unvisitedVertex_index as
            //index of certain vertex in List_Vertices in graph type
            if (graph->List_Vertices[unvisitedVertex_index]->label == val)
            {
                for (i = 0; i < graph->vertexCount; i++)
                {
                    graph->List_Vertices[i]->visited = false;
                }
                return unvisitedVertex_index;
            }
        }
    }

    //stack is empty, search is complete, reset the visited flag for each node
    for (i = 0; i < graph->vertexCount; i++)
    {
        graph->List_Vertices[i]->visited = false;
    }
    return -1;
}
