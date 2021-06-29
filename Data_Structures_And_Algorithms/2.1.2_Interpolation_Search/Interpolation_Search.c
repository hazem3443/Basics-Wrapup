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

int find(int *arr, int data)
{
    int lowerBound = 0;
    int upperBound = MAX - 1;
    int midPoint = -1;

    while (lowerBound <= upperBound)
    {
        // midPoint = (lowerBound + upperBound) / 2;
        // midPoint = lowerBound + (upperBound - lowerBound) / 2;
        midPoint = lowerBound + (((double)(upperBound - lowerBound) / (arr[upperBound] - arr[lowerBound])) * (data - arr[lowerBound]));
        // data found
        if (arr[midPoint] == data)
            return midPoint;
        else if (arr[midPoint] < data)
        {
            // if data is larger
            // data is in upper half
            lowerBound = midPoint + 1;
        }
        else
        {
            // data is smaller
            // data is in lower half
            upperBound = midPoint - 1;
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
        printf("\nElement not found.\n");
}