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
NodeType *deleteFirst(NodeType **head);               // O(1)
NodeType *find(NodeType *head, int key);              // O(n)
bool isEmpty(NodeType *head);                         // O(1)
int length(NodeType *head);                           // O(n)

void insert(NodeType **head, int at_key, int new_key, int new_data); // O(n)
NodeType *delete (NodeType **head, int key);                         // O(n)
void reverse(NodeType **head);                                       // O(n)
void sortASC(NodeType *head);                                        // O(n(n-1)) ~= O(n^2)

void replace(NodeType **head, int at_key, int new_key, int new_data); // O(n)

void main()
{
    // for and opertaion that require modification to head we need to pass it's reference to modify it globally or return it'smodified value and assign it back to the global pointer
    insertFirst(&head1, 3, 12); // here we need to modify head1 pointer to point to the newly created node that points to the head pointer
    insertFirst(&head1, 2, 11);
    insertFirst(&head1, 1, 10);
    insertFirst(&head1, 4, 100);

    printList(head1);
    reverse(&head1);
    printList(head1);

    insert(&head1, 3, 4, 6);
    printf("After Insert at key 2 ->");
    printList(head1);

    replace(&head1, 4, 15, 10);
    printf("After Replacing node of key 4 ->");
    printList(head1);

    printf("AFTER Sorting:");
    sortASC(head1);
    printList(head1);

    NodeType *foundNode = find(head1, 2);
    if (foundNode != NULL)
        printf("Element found: (%d,%d)\n", foundNode->key, foundNode->data);
    else
        printf("Element not found.\n");

    printf("Linked list Length = %i\n", length(head1));

    NodeType *elment = delete (&head1, 2);
    printf("List after deleting an item: (%d,%d) \n", elment->key, elment->data);
    free(elment);
    // free(delete (&head1, 1)); //free allocated node that is deleted
    printList(head1);

    while (!isEmpty(head1))
    {
        NodeType *temp = deleteFirst(&head1);
        printf("Deleted value:(%d,%d) \n", temp->key, temp->data);
        free(temp); // free allocated memory after deleting it from the list
    }
}
// Wrap functions
//  Linked List Traversion
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

// delete first item
NodeType *deleteFirst(NodeType **head)
{
    // save reference to first link
    NodeType *tempLink = *head;
    // mark next to first link as first
    *head = (*head)->next;

    // return the deleted link

    return tempLink;
}

// find a link with given key
NodeType *find(NodeType *head, int key)
{
    // if list is empty
    if (head == NULL)
    {
        return NULL;
    }

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

// is list empty
bool isEmpty(NodeType *head)
{
    return head == NULL;
}
// length of linked list
int length(NodeType *head)
{
    NodeType *current;
    int length = 0;

    for (current = head; current != NULL; current = current->next)
    {
        length++;
    }

    return length;
}
// delete a link with given key
NodeType *delete (NodeType **head, int key)
{
    // start from the first Node
    NodeType *current = *head;
    NodeType *previous = NULL;

    // if list is empty
    if (*head == NULL)
        return NULL;

    // navigate through list
    while (current->key != key)
    {
        // if it is last node
        if (current->next == NULL)
            return NULL;
        else
        {
            // store reference to current Node
            previous = current;
            // move to next Node
            current = current->next;
        }
    }

    // found a match in current pointer, update the Node
    if (current == *head)
        *head = (*head)->next; // change head to point to next Node
    else
        previous->next = current->next; // bypass the current Node

    return current;
}

void reverse(NodeType **head)
{
    NodeType *prev = NULL;
    NodeType *current = *head;
    NodeType *next;

    while (current != NULL) // break if current is the linked list end
    {
        next = current->next; // save next Node pointer before modification
        current->next = prev; // reverse next pointer to previous
        prev = current;       // save
        current = next;       // move to next node
    }

    *head = prev;
}

void sortASC(NodeType *head) // bubble Sort occurs by swapping values of each node and keep tree as it is
{
    // keep the nodes as it is but swap key and value of each node
    int i, j, k, tempKey, tempData;
    NodeType *current;
    NodeType *next;

    int size = length(head);
    k = size;
    for (i = 0; i < size - 1; i++, k--)
    {
        current = head;
        next = current->next;

        for (j = 1; j < k; j++)
        {
            // printList(*head);
            if (current->data > next->data)
            {
                tempData = current->data;
                current->data = next->data;
                next->data = tempData;

                tempKey = current->key;
                current->key = next->key;
                next->key = tempKey;
            }
            current = current->next;
            next = current->next;
        }
    }
}

void insert(NodeType **head, int at_key, int new_key, int new_data)
{
    // start from the first Node
    NodeType *current = *head;
    NodeType *previous = NULL;

    // if list is empty
    if (*head == NULL)
        insertFirst(head, new_key, new_data);

    // navigate through list
    while (current->key != at_key)
    {
        // if it is last node
        if (current->next == NULL)
        {
            printf("key Not Found\n");
            return; // key not found
        }
        else
        {
            // store reference to current Node
            previous = current;
            // move to next Node
            current = current->next;
        }
    }

    // found a match in current pointer, update the Node
    if (current == *head)
        insertFirst(head, new_key, new_data); // change head to point to next Node
    else
    {
        NodeType *Node = (NodeType *)malloc(sizeof(NodeType));

        Node->key = new_key;
        Node->data = new_data;

        // point it to old first node
        Node->next = current;
        previous->next = Node; // bypass the current Node
    }

    return;
}

void replace(NodeType **head, int at_key, int new_key, int new_data)
{
    // start from the first Node
    NodeType *current = *head;
    NodeType *previous = NULL;

    // if list is empty
    if (*head == NULL)
        printf("List is empty\n");

    // navigate through list
    while (current->key != at_key)
    {
        // if it is last node
        if (current->next == NULL)
        {
            printf("key Not Found");
            return; // key not found
        }
        else
        {
            // store reference to current Node
            previous = current;
            // move to next Node
            current = current->next;
        }
    }

    // found a match in current pointer, update the Node
    if (current == *head)
    {
        deleteFirst(head);
        insertFirst(head, new_key, new_data); // change head to point to next Node
    }

    else
    {
        free(delete (head, at_key));
        insert(head, (previous->next)->key, new_key, new_data);
    }

    return;
}