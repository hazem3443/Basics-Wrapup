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

int *test(int *x);

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
void main()
{
    int *x;
    x = test(arr);
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%i", x[i]);
    }
    printf("\n");
}
int *test(int *x)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%i", x[i]);
    }
    printf("\n");
    x[0] = 5;
    return x;
}