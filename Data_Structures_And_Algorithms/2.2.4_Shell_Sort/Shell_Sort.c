#include <stdio.h>
#include <stdbool.h>

void swapByReference(int *x, int *y);

void Shell_Sort(int *x, int len, bool asc);
void printList(int *x, int len);

void main()
{
    // int x = 10, y = 5;
    // printf("before swapping -> x = %i, y = %i\n", x, y);
    // swapByReference(&x, &y);
    // printf("after swapping -> x = %i, y = %i\n", x, y);
    // printf("arr len = %lu\n", sizeof(arr) / sizeof(int));

    int arr[] = {10, 22, 3, 4, 5, 6};
    int len = sizeof(arr) / sizeof(int);
    Shell_Sort(arr, len, 1);
    printList(arr, len);
}

void swapByReference(int *x, int *y)
{                 //O(3) -- S(0)
    *x = *y + *x; //x= x+y
    *y = *x - *y; //y = x+y-y = x
    *x = *x - *y; //x = x+y-x = y
}

void Shell_Sort(int *x, int len, bool asc)
{
    // int j, i;
    int valueToInsert;
    int interval = 1;

    //choose proper interval
    // len = 0 to 2 , interval = 1          iter#0
    // len = 3 to 11 , interval = 4         iter#1
    // len = 12 to 38 , interval = 13       iter#2
    // len = 39 to 119 , interval = 40      iter#3
    // len = 120 to 362 , interval = 121    iter#4
    // len = 363 to 1092 , interval = 364   iter#5
    // len = 1093 to 3278 , interval = 1093 iter#6
    // len = 3279 to 9839 , interval = 3280 iter#7

    while (interval <= len / 3)
    {
        interval = interval * 3 + 1;
    }

    while (interval > 0)
    { //loop over interval iterations
        // printf("iteration %d#:\n", i++);

        //conditional insertion sort with interval initialization step
        //in insertion sort we start from i = 1
        for (int i = interval; i < len; i++)
        {
            valueToInsert = x[i];

            if (asc == 1)
            {
                //and here in insertion sort we decrement by 1
                for (int j = i; j > interval - 1 && x[j - interval] > valueToInsert; j -= interval)
                    swapByReference(x + j, x + j - interval);
            }
            else
            {
                for (int j = i; j > interval - 1 && x[j - interval] < valueToInsert; j -= interval)
                    swapByReference(x + j, x + j - interval);
            }
        }
        //reverse the generation loop of interval value
        interval = (interval - 1) / 3; //re-iterate recursively
    }
}

void printList(int *x, int len)
{
    for (int i = 0; i < len; i++)
        printf("arr[%i] = %i\n", i, x[i]);
}
