#include <stdio.h>
#include <stdbool.h>

void swapByReference(int *x, int *y);

void Quick_Sort(int *x, int len, bool asc);

void quick_logic(int *x, int left, int right, bool asc);
int partition(int *arr, int left, int right, int pivot, bool asc);

void printList(int *x, int len);

void main()
{
    int arr[] = {4, 6, 3, 2, 8, 8, 9};
    int len = sizeof(arr) / sizeof(int);

    Quick_Sort(arr, len, 0);
    printList(arr, len);
}

void swapByReference(int *x, int *y)
{ //O(3) -- S(0)
    //bug: it the two values points to the same reference it is not gona work
    //because both x and y points to the same resource

    //bug fix
    if (x == y)
        return;

    // printf("1- %i,2- %i\n", *x, *y);
    *x = *y + *x; //x= x+y
    // printf("1- %i,2- %i\n", *x, *y);

    *y = *x - *y; //y = x+y-y = x
    *x = *x - *y; //x = x+y-x = y
    // printf("1- %i,2- %i\n", *x, *y);
}

void Quick_Sort(int *x, int len, bool asc)
{
    quick_logic(x, 0, len - 1, asc);
}
int partition(int *arr, int left, int right, int pivot, bool asc)
{
    //input array {4, 6, 3, 2, 1, 9, 7} left= 0, right=6, pivot=7
    //left,right are indexes pivot is value of arr[right]
    int leftPointer = left - 1;
    int rightPointer = right;

    if (asc == 1)
    {
        while (true)
        {
            while (arr[++leftPointer] < pivot)
                ; //just to move leftPointer till this condition is violated

            while (rightPointer > 0 && arr[--rightPointer] > pivot)
                ; //just to move rightPointer till this condition is violated

            if (leftPointer >= rightPointer)
                break;
            else
            {
                printf(" item swapped :%d,%d\n", arr[leftPointer], arr[rightPointer]);
                swapByReference(arr + leftPointer, arr + rightPointer);
            }
        }
    }
    else
    {
        while (true)
        {
            while (arr[++leftPointer] > pivot)
                ;

            while (rightPointer > 0 && arr[--rightPointer] < pivot)
                ;

            if (leftPointer >= rightPointer)
                break;
            else
            {
                printf(" item swapped :%d,%d\n", arr[leftPointer], arr[rightPointer]);
                swapByReference(arr + leftPointer, arr + rightPointer);
            }
        }
    }

    printf(" pivot swapped :%d,%d\n", arr[leftPointer], arr[right]);
    swapByReference(arr + leftPointer, arr + right);
    printf("Updated Array: ");
    printList(arr, 7);

    return leftPointer;
}

void quick_logic(int *x, int left, int right, bool asc)
{
    if (right - left <= 0) //stoping condition of recursive function
        return;
    else
    {
        int pivot = x[right];
        int partitionPoint = partition(x, left, right, pivot, asc);

        quick_logic(x, left, partitionPoint - 1, asc);
        quick_logic(x, partitionPoint + 1, right, asc);
    }
}
void printList(int *x, int len)
{
    // printf("\n");
    for (int i = 0; i < len; i++)
        // printf("arr[%i] = %i\n", i, x[i]);
        printf(" %i,", x[i]);
    printf("\b \n");
}
