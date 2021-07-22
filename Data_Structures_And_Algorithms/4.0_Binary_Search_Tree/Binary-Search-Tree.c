#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node Node_Type;

void insert(Node_Type **root, int data);
Node_Type *search(Node_Type **root, int data);

void pre_order_traversal(Node_Type *root);
void inorder_traversal(Node_Type *root);
void post_order_traversal(Node_Type *root);

Node_Type *treeroot1 = NULL;

void main()
{
    int i;
    int array[7] = {27, 14, 35, 10, 19, 31, 42};

    for (i = 0; i < 7; i++)
        insert(&treeroot1, array[i]);

    printf("ptr = %i\n", treeroot1->rightChild->leftChild->data);

    Node_Type *temp = search(&treeroot1, 31);

    if (temp != NULL)
    {
        printf("[%d] Element found.", temp->data);
        printf("\n");
    }
    else
    {
        printf("[ x ] Element not found (%d).\n", i);
    }

    temp = search(&treeroot1, 15);

    if (temp != NULL)
    {
        printf("[%d] Element found.", temp->data);
        printf("\n");
    }
    else
    {
        printf("[ x ] Element not found (%d).\n", i);
    }

    printf("\nPreorder traversal: ");
    pre_order_traversal(treeroot1);

    printf("\nInorder traversal: ");
    inorder_traversal(treeroot1);

    printf("\nPost order traversal: ");
    post_order_traversal(treeroot1);
    printf("\n");
}

void insert(Node_Type **root, int data)
{

    Node_Type *tempNode = (Node_Type *)malloc(sizeof(Node_Type));
    Node_Type *current;
    Node_Type *parent;

    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    //if tree is empty
    if (*root == NULL)
        *root = tempNode;
    else
    {
        current = *root;
        parent = NULL;

        while (parent = current)
        {
            //go to left of the tree
            if (data < parent->data)
            {
                current = current->leftChild;
                //insert to the left if it is empty
                if (current == NULL)
                {
                    parent->leftChild = tempNode;
                    return;
                }
            } //go to right of the tree
            else
            {
                current = current->rightChild;
                //insert to the right if it is empty
                if (current == NULL)
                {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

Node_Type *search(Node_Type **root, int data)
{
    Node_Type *current = *root;
    printf("Visiting elements: ");

    while (current->data != data)
    {
        if (current != NULL)
            printf("%d ", current->data);

        //go to left tree
        if (current->data > data)
        {
            current = current->leftChild;
        }
        //else go to right tree
        else
        {
            current = current->rightChild;
        }

        //not found
        if (current == NULL)
            return NULL;
    }
    return current;
}

void pre_order_traversal(Node_Type *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        pre_order_traversal(root->leftChild);
        pre_order_traversal(root->rightChild);
    }
}

void inorder_traversal(Node_Type *root)
{
    if (root != NULL)
    {
        inorder_traversal(root->leftChild);
        printf("%d ", root->data);
        inorder_traversal(root->rightChild);
    }
}

void post_order_traversal(Node_Type *root)
{
    if (root != NULL)
    {
        post_order_traversal(root->leftChild);
        post_order_traversal(root->rightChild);
        printf("%d ", root->data);
    }
}