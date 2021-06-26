#include <stdio.h>

#define MAX 20

// array of items on which linear search will be conducted.
int intArray[MAX] = {1, 2, 3, 4, 6, 7, 9, 11, 12, 14, 15, 16, 17, 19, 33, 34, 43, 45, 55, 66};

void printline(int count)
{
    int i;

    for (i = 0; i < count - 1; i++)
    {
        printf("=");
    }

    printf("=\n");
}

// this method makes a linear search.
int find(int *arr, int data)
{
    int i;
    // navigate through all items
    for (i = 0; i < MAX; i++)
    {
        // if data found, break the loop
        if (data == arr[i])
        {
            return i;
        }
    }
    return -1;
}

void display()
{
    int i;
    printf("[");

    // navigate through all items
    for (i = 0; i < MAX; i++)
    {
        printf("%d ", intArray[i]);
    }

    printf("]\n");
}

void main()
{
    printf("Input Array: ");
    display();
    printline(70);

    //find location of 1
    int location = find(intArray, 55);

    // if element was found
    if (location != -1)
        printf("\nElement found at location: %d\n", (location));
    else
        printf("Element not found.");
}