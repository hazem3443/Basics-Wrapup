#include <stdio.h>
#include <stdbool.h>

void swapByReference(int *x, int *y);

void SortSelectionly(int *x, int len, bool asc);
void printList(int *x, int len);

void main()
{
    // int x = 10, y = 5;
    // printf("before swapping -> x = %i, y = %i\n", x, y);
    // swapByReference(&x, &y);
    // printf("after swapping -> x = %i, y = %i\n", x, y);
    // printf("arr len = %lu\n", sizeof(arr) / sizeof(int));

    int arr[] = {10, 22, 3, 4, 5, 6, 70};
    int len = sizeof(arr) / sizeof(int);
    SortSelectionly(arr, len, 0);
    printList(arr, len);
}

void swapByReference(int *x, int *y)
{                 //O(3) -- S(0)
    *x = *y + *x; //x= x+y
    *y = *x - *y; //y = x+y-y = x
    *x = *x - *y; //x = x+y-x = y
}

void SortSelectionly(int *x, int len, bool asc)
{
    int i_min;

    for (size_t j = 0; j < len; j++)
    {
        i_min = j;
        for (size_t i = j + 1; i < len; i++)
        {
            if (asc == 1)
            {
                if (x[i] < x[i_min])
                {
                    i_min = i;
                }
            }
            else
            {
                if (x[i] > x[i_min])
                {
                    i_min = i;
                }
            }
        }

        if (i_min != j)
        {
            swapByReference(x + i_min, x + j);
        }
    }
}

void printList(int *x, int len)
{
    for (int i = 0; i < len; i++)
        printf("arr[%i] = %i\n", i, x[i]);
}
