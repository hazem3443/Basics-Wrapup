#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void swapByReference(int *x, int *y);

int *divide_merge(int *x, int len, bool asc);
int *merge(int *l1, int l1_len, int *l2, int l2_len, int *x, bool asc);

void sort(int *x, int *y, int low, int high);
void merging(int *x, int *y, int low, int mid, int high);

void Merge_Sort(int *x, int len, bool asc);

void printList(int *x, int len);

void main()
{
    // int x = 10, y = 5;
    // printf("before swapping -> x = %i, y = %i\n", x, y);
    // swapByReference(&x, &y);
    // printf("after swapping -> x = %i, y = %i\n", x, y);
    // printf("arr len = %lu\n", sizeof(arr) / sizeof(int));

    int arr[] = {10, 22, 3, 4, 5, 6, 63, 548, 2304, 2, 1, 1, 2, 2, 3};

    int len = sizeof(arr) / sizeof(int);
    Merge_Sort(arr, len, 1);

    printList(arr, len);
}

void swapByReference(int *x, int *y)
{                 // O(3) -- S(0)
    *x = *y + *x; // x= x+y
    *y = *x - *y; // y = x+y-y = x
    *x = *x - *y; // x = x+y-x = y
}

void Merge_Sort(int *x, int len, bool asc)
{
    // //tutorials point methodology
    // int *y;
    // y = (int *)malloc((len ) * sizeof(int *));
    // // printf("bef x = %p y = %p y[0]=%i\n", x, y, y[0]);

    // sort(x, y, 0, len - 1); //this will divide iteratively

    // // printf("aft x = %p y = %p y[0]=%i\n", x, y, y[0]);
    // memcpy(x, y, len);
    // ----------------
    // ----------------
    // ----------------

    // my methodology
    divide_merge(x, len, asc);
}
void sort(int *x, int *y, int low, int high)
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;
        // printf("in sort x = %p low = %i mid=%i high = %i y = %p y[0]=%i\n", x, low, mid, high, y, y[0]);
        sort(x, y, low, mid);
        sort(x, y, mid + 1, high);

        merging(x, y, low, mid, high); // this will merge iteratively too
    }
    else
    {
        return;
    }
}

void merging(int *x, int *y, int low, int mid, int high)
{
    int l1, l2, i;

    for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++)
    {
        if (x[l1] <= x[l2])
            y[i] = x[l1++];
        else
            y[i] = x[l2++];
    }

    while (l1 <= mid)
        y[i++] = x[l1++];

    while (l2 <= high)
        y[i++] = x[l2++];

    for (i = low; i <= high; i++)
        x[i] = y[i];
}

int *divide_merge(int *x, int len, bool asc)
{
    if (len == 1)
        return x;

    int mid = (len) / 2;

    int *l1 = divide_merge(x, mid, asc);
    int *l2 = divide_merge(x + mid, len - mid, asc);

    int *new_merged_arr = merge(l1, mid, l2, len - mid, x, asc);

    return new_merged_arr;
}
int *merge(int *l1, int l1_len, int *l2, int l2_len, int *x, bool asc)
{
    int *l3 = (int *)malloc((l1_len + l2_len) * sizeof(int *));

    int i = 0, j = 0;
    int new_i = 0;
    while (i < l1_len && j < l2_len)
    {
        if (asc == 1)
        {
            if (l1[i] <= l2[j])
                l3[new_i++] = l2[j++];
            else
                l3[new_i++] = l1[i++];
        }
        else
        {
            if (l1[i] <= l2[j])
                l3[new_i++] = l1[i++];
            else
                l3[new_i++] = l2[j++];
        }
    }
    while (i < l1_len)
    {
        l3[new_i++] = l1[i++];
    }
    while (j < l2_len)
    {
        l3[new_i++] = l2[j++];
    }
    // memcpy(x, l3, (l1_len + l2_len) * sizeof(int));

    // like memcpy function
    l1_len += l2_len;
    l2_len = 0;
    while ((x[l2_len] = l3[l2_len]) && ++l2_len < l1_len)
        ;

    free(l3);
    return x;
}

void printList(int *x, int len)
{
    for (int i = 0; i < len; i++)
        printf("arr[%i] = %i\n", i, x[i]);
}
