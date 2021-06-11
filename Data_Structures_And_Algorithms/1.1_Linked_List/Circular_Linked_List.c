#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int key;

    struct node *next;
} NodeType;

void PrintList(NodeType *head);
void InsertFirst(NodeType **head, int key, int data);
NodeType *DeleteFirst(NodeType **head);
bool isEmpty(NodeType *head);
size_t Length(NodeType *head);

NodeType *head1 = NULL;
void main()
{
    // printf("head out= %p\n", head1);
    printf("is Empty %i\n", isEmpty(head1));

    InsertFirst(&head1, 1, 10);
    InsertFirst(&head1, 2, 11);
    InsertFirst(&head1, 3, 12);
    InsertFirst(&head1, 4, 13);

    printf("Length = %lu\n", Length(head1));

    PrintList(head1);
    while (!isEmpty(head1))
    {
        NodeType *DeletedNode = DeleteFirst(&head1);
        printf("DeletedNode = %p (%d,%d)\n", DeletedNode, DeletedNode->key, DeletedNode->data);
        free(DeletedNode);
    }

    printf("is Empty %i\n", isEmpty(head1));
    printf("Length = %lu\n", Length(head1));
}
void PrintList(NodeType *head)
{
    NodeType *current = head;
    printf("[ ");
    if (head != NULL) //not empty list
    {
        while (1)
        {
            printf("(%d,%d),", current->key, current->data);
            // printf("head = %p -current = %p (%d,%d) next=%p,\n", head, current, current->key, current->data, current->next);
            //to continuously read the list and perform a circular read you can comment this if condition and leave just current = current->next which moves the cursor to next node
            if (current->next == head)
                break;
            else
                current = current->next;
        }
        //now current is the head
    }
    printf("\b ]\n");
}
void InsertFirst(NodeType **head, int key, int data)
{
    NodeType *Node = (NodeType *)malloc(sizeof(NodeType));
    Node->key = key;
    Node->data = data;

    if (*head == NULL) //is linked list empty
        ((*head) = Node) && ((Node->next) = Node);
    else
    {
        NodeType *current = *head;
        NodeType *previous = NULL;

        //check final node then move
        while (current->next != *head)
        {
            current = current->next;
        }
        //now current = final node
        current->next = Node; //update final node to be the new node

        Node->next = *head; //update the node-> next to be head
        *head = Node;       // update the head to be the newly created node
    }
}

NodeType *DeleteFirst(NodeType **head)
{
    NodeType *current = *head;
    if (current->next == *head)
    {
        *head = NULL;
        return current;
    }
    else
    {
        while (current->next != *head)
        {
            current = current->next;
        }

        //now current = final node
        current->next = (*head)->next;
        NodeType *tempNode = *head;
        *head = (*head)->next;
        return tempNode;
    }
}

bool isEmpty(NodeType *head)
{
    return head == NULL;
}

size_t Length(NodeType *head)
{
    NodeType *current = head;
    size_t i = 0;
    while (current != NULL && current->next != head)
    {
        i++;
        current = current->next;
    }
    return (current == NULL) ? i : ++i;
}
