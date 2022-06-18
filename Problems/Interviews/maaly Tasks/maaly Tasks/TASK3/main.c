#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int key;
    struct node *next;
} NodeType;

NodeType *head1 = NULL;
NodeType *current = NULL;

void printList(NodeType *head);                       // O(n) where n is the number of n node in the linked list
void insertFirst(NodeType **head, int key, int data); // O(1)
NodeType *find(NodeType *head, int key);              // O(n)

void deleteNodeWithoutHead(NodeType * pos); // O(1)

void main()
{
    // for and opertaion that require modification to head we need to pass it's reference to modify it globally or return it'smodified value and assign it back to the global pointer
    insertFirst(&head1, 3, 12); // here we need to modify head1 pointer to point to the newly created node that points to the head pointer
    insertFirst(&head1, 2, 11);
    insertFirst(&head1, 1, 10);
    insertFirst(&head1, 4, 100);

    printList(head1);
    NodeType *foundNode = find(head1, 1);
    deleteNodeWithoutHead(foundNode);
    printList(head1);
}

//  Linked List Traversal
void printList(NodeType *head)
{
    printf("[ ");

    NodeType *ptr = head;
    // start from the beginning
    while (ptr != NULL)
    {
        printf("(%d,%d)", (ptr)->key, (ptr)->data);
        ptr = (ptr)->next;
    }

    printf(" ]\n");
}

// insert Node at the first location
void insertFirst(NodeType **head, int key, int data)
{
    // create a Node by allocation memory sizeof(NodeType) and cast the malloced address to
    NodeType *Node = (NodeType *)malloc(sizeof(NodeType));

    Node->key = key;
    Node->data = data;

    // point it to old first node
    Node->next = *head;

    // point first to new first node
    *head = Node;
}

// find a link with given key
NodeType *find(NodeType *head, int key)
{
    // if list is empty
    if (head == NULL)
        return NULL;

    // start from the first link
    NodeType *current = head;

    // navigate through list
    while (current->key != key)
    {

        // if it is last node
        if (current->next == NULL)
        {
            return NULL;
        }
        else
        {
            // go to next link
            current = current->next;
        }
    }

    // if data found, return the current Link
    return current;
}

void deleteNodeWithoutHead(NodeType * pos)
{
    if (pos == NULL) // If linked list is empty
        return;
    else {
 
        if (pos->next == NULL) {
            printf("This is last node, require head, can't "
                   "be freed\n");
            return;
        }
 
        NodeType* temp = pos->next;//next node to node to be deleted
 
        // Copy data of the next node to current node
        pos->data = pos->next->data;
        pos->key = pos->next->key;
 
        // Perform conventional deletion
        pos->next = pos->next->next;
 
        free(temp);
    }
}