#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    struct node *next;
    int key;
    int data;
    struct node *prev;
} NodeType;

typedef struct liked_list
{
    NodeType *head;
    NodeType *tail;
} LinkedList_Type;

void PreviewList(LinkedList_Type ll);
void InsertFirst(LinkedList_Type *ll_ref, int key, int data);
NodeType *DeleteFirst(LinkedList_Type *ll_ref);
size_t length(LinkedList_Type ll);
bool isEmpty(LinkedList_Type ll);

NodeType *Find(LinkedList_Type ll, int key);
void Insert(LinkedList_Type *ll_ref, int at_key, int key, int data);
NodeType *delete (LinkedList_Type *ll_ref, int at_key);
void update(LinkedList_Type *ll_ref, int at_key, int key, int data);
void Reverse(LinkedList_Type *ll_ref);

void main()
{
    LinkedList_Type linkedlist1;
    InsertFirst(&linkedlist1, 1, 10);
    InsertFirst(&linkedlist1, 2, 11);
    InsertFirst(&linkedlist1, 3, 12);

    // printf("current_head out->%p\n", linkedlist1.head);
    // printf("current_tail out->%p\n", linkedlist1.tail);
    PreviewList(linkedlist1);

    size_t len = length(linkedlist1);
    printf("linked list length %lu\n", len);
    PreviewList(linkedlist1);

    NodeType *found_Node = Find(linkedlist1, 2);
    if (found_Node != NULL)
        printf("found Element (%d,%d)\n", found_Node->key, found_Node->data);

    PreviewList(linkedlist1);

    Insert(&linkedlist1, 2, 5, 15);
    printf("After Insert at key 5 -> ");
    PreviewList(linkedlist1);

    update(&linkedlist1, 5, 5, 150);
    printf("After Updating value of key 5 -> ");
    PreviewList(linkedlist1);

    NodeType *Deleted_node = delete (&linkedlist1, 5);
    free(Deleted_node);
    printf("After Delete node of key 5->");
    PreviewList(linkedlist1);

    printf("Before Reversion: ");
    PreviewList(linkedlist1);
    printf("After Reversion: ");
    Reverse(&linkedlist1);
    PreviewList(linkedlist1);

    while (!isEmpty(linkedlist1))
    {
        NodeType *deletedNode = DeleteFirst(&linkedlist1);
        printf("node (%d,%d) Deleted\n", deletedNode->key, deletedNode->data);
        free(deletedNode);
    }
    PreviewList(linkedlist1);
}

void InsertFirst(LinkedList_Type *ll_ref, int key, int data)
{
    NodeType *Node = (NodeType *)malloc(sizeof(NodeType));
    // printf("head -> %p\n", *head_ref);

    Node->next = ll_ref->head;

    Node->key = key;
    Node->data = data;

    Node->prev = NULL;
    if (!isEmpty(*ll_ref))
        (ll_ref->head)->prev = Node;
    (ll_ref->head) = Node;

    // printf("current_head->%p\n", ll_ref->head);
    // printf("current_tail->%p\n", ll_ref->tail);

    // printf("Node next -> %p\n", Node->next);
    // printf("Node prev -> %p\n", Node->prev);
    // printf("key -> %i\n", Node->key);
    // printf("data -> %i\n", Node->data);
}
void PreviewList(LinkedList_Type ll)
{
    NodeType *current_head = ll.head;
    NodeType *current_tail = ll.tail;
    // printf("current_head preview->%p\n", current_head);
    // printf("current_tail preview->%p\n", current_tail);

    printf("[ ");
    while (current_head != NULL)
    {
        printf("(%i,%i),", current_head->key, current_head->data);
        current_head = current_head->next;
    }
    printf("\b ]\n");
}

NodeType *DeleteFirst(LinkedList_Type *ll_ref)
{
    NodeType *current = ll_ref->head;

    ll_ref->head = (ll_ref->head)->next;
    return current;
}

size_t length(LinkedList_Type ll)
{
    size_t i = 0;
    NodeType *current = ll.head;
    while (current != NULL)
    {
        i++;
        // printf("(%i,%i),", current_head->key, current_head->data);
        current = current->next;
    }
    return i;
}

bool isEmpty(LinkedList_Type ll)
{
    return ll.head == NULL;
}

NodeType *Find(LinkedList_Type ll, int key)
{
    NodeType *current = ll.head;

    if (isEmpty(ll))
    {
        printf("Linked List is Empty\n");
        return NULL;
    }

    while (current->key != key)
    {
        if (current->next == NULL || current == NULL)
        {
            // reached the end without finding the node with that key
            printf("Node Not Found\n");
            return NULL;
        }
        current = current->next;
    }
    // now current have the node with that at_key
    return current;
}

void Insert(LinkedList_Type *ll_ref, int at_key, int key, int data)
{
    NodeType *found_Node = Find(*ll_ref, at_key);

    if (!isEmpty(*ll_ref) && found_Node == NULL)
    { // element not found
        printf("Element NOT found\n");
        return;
    }

    if (found_Node == ll_ref->head)
    { // element at head
        InsertFirst(ll_ref, key, data);
    }
    else
    {
        NodeType *Node = (NodeType *)malloc(sizeof(NodeType));

        Node->next = found_Node;

        Node->key = key;
        Node->data = data;

        Node->prev = found_Node->prev;
        (found_Node->prev)->next = Node;

        found_Node->prev = Node;
    }
}

NodeType *delete (LinkedList_Type *ll_ref, int at_key)
{
    NodeType *Found_Node = Find(*ll_ref, at_key);

    (Found_Node->prev)->next = Found_Node->next;
    (Found_Node->next)->prev = (Found_Node->prev);
    return Found_Node;
}

void update(LinkedList_Type *ll_ref, int at_key, int key, int data)
{
    NodeType *Found_Node = Find(*ll_ref, at_key);
    Found_Node->key = key;
    Found_Node->data = data;
}

void Reverse(LinkedList_Type *ll_ref)
{
    NodeType *current = ll_ref->head;
    NodeType *Temp_ptr;
    while (current != NULL)
    {
        // printf("Befor current =%p  prev =%p  (%i,%i) next=%p \n", current, current->prev, current->key, current->data, current->next);

        Temp_ptr = current->next;
        current->next = current->prev;
        current->prev = Temp_ptr;

        // printf("After current =%p  prev =%p  (%i,%i) next=%p \n", current, current->prev, current->key, current->data, current->next);
        if (current->prev == NULL)
        {
            break;
        }
        current = Temp_ptr;
    }
    ll_ref->head = current;
}