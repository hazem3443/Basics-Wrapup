#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct Queue_type
{
    int intArray[MAX];
    int front; //first filled position in the queue
    int rear;  //last available position in the queue
    int itemCount;
} Queue;

Queue q1 = {{0}, 0, -1, 0};
int peek(Queue *queue);
bool isEmpty(Queue *queue);
bool isFull(Queue *queue);

int size(Queue *queue);

void insert(Queue *queue, int data);
int removeData(Queue *queue);

int main()
{
    /* insert 5 items */
    insert(&q1, 3);
    insert(&q1, 5);
    insert(&q1, 9);
    insert(&q1, 1);
    insert(&q1, 12);

    // front : 0
    // rear  : 4
    // ------------------
    // index : 0 1 2 3 4
    // ------------------
    // queue : 3 5 9 1 12
    insert(&q1, 15);

    // front : 0
    // rear  : 5
    // ---------------------
    // index : 0 1 2 3 4  5
    // ---------------------
    // queue : 3 5 9 1 12 15

    if (isFull(&q1))
    {
        printf("Queue is full!\n");
    }

    // remove one item
    int num = removeData(&q1);

    printf("Element removed: %d\n", num);
    // front : 1
    // rear  : 5
    // -------------------
    // index : 1 2 3 4  5
    // -------------------
    // queue : 5 9 1 12 15

    // insert more items
    insert(&q1, 16);

    // front : 1
    // rear  : -1
    // ----------------------
    // index : 0  1 2 3 4  5
    // ----------------------
    // queue : 16 5 9 1 12 15

    // As queue is full, elements will not be inserted.
    insert(&q1, 17);
    insert(&q1, 18);

    // ----------------------
    // index : 0  1 2 3 4  5
    // ----------------------
    // queue : 16 5 9 1 12 15
    printf("Element at front: %d\n", peek(&q1));

    printf("----------------------\n");
    printf("index : 5 4 3 2  1  0\n");
    printf("----------------------\n");
    printf("Queue:  ");

    while (!isEmpty(&q1))
    {
        int n = removeData(&q1);

        printf("%d ", n);
    }

    printf("\n");
    printf("front = %i, rear = %i, itemcount = %i\n", q1.front, q1.rear, q1.itemCount);
    insert(&q1, 10);
    insert(&q1, 20);
    insert(&q1, 30);
    insert(&q1, 40);

    printf("front = %i, rear = %i, itemcount = %i\n", q1.front, q1.rear, q1.itemCount);
    while (!isEmpty(&q1))
    {
        int n = removeData(&q1);

        printf("%d ", n);
    }
    printf("\n");
    printf("front = %i, rear = %i, itemcount = %i\n", q1.front, q1.rear, q1.itemCount);
}

int removeData(Queue *queue) //dequeue
{
    if (!isEmpty(queue))
    {
        int data = queue->intArray[queue->front++];

        if (queue->front == MAX) //move front to 0 if it touches the head
        {
            queue->front = 0;
        }

        queue->itemCount--;
        return data;
    }
}
void insert(Queue *queue, int data) //enqueue
{
    if (!isFull(queue))
    {
        if (queue->rear == MAX - 1) //move rear to -1 if it touches last position in the array
        {                           //max-1 to avoid segmentation error
            queue->rear = -1;
        }

        queue->intArray[++queue->rear] = data;
        queue->itemCount++;
    }
}
int size(Queue *queue)
{
    return queue->itemCount;
}
bool isFull(Queue *queue)
{
    return queue->itemCount == MAX;
}
bool isEmpty(Queue *queue)
{
    return queue->itemCount == 0;
}
int peek(Queue *queue)
{
    return queue->intArray[queue->front];
}