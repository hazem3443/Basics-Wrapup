#include <stdio.h>
#include <string.h>

typedef struct ArraY_Type
{
    /* data */
    int *arr;
    long unsigned int len;
} ArrType;

void Traverse_over_Array(ArrType *arr);
ArrType insert_element_intoArray(ArrType *arr, int element_to_insert, int at_index);
ArrType Delete_element_fromArray(ArrType *arr, int at_index);
int Search_in_Array(ArrType *arr, int search_for_this_item);
ArrType Update_element_at_Array(ArrType *arr, int value_to_update, int at_index);

void main()
{
    int LA[] = {1, 3, 5, 7, 8};

    ArrType x;
    x.arr = LA;
    x.len = (sizeof(LA) / sizeof(int));

    printf("Original Array\n");
    Traverse_over_Array(&x);

    printf("array After insertion Operation\n");
    ArrType a = insert_element_intoArray(&x, 11, 3);
    Traverse_over_Array(&a);

    printf("array After delete Operation\n");
    ArrType b = Delete_element_fromArray(&a, 3);
    Traverse_over_Array(&b);

    printf("index of Search item\n");
    int index = Search_in_Array(&b, 8);
    printf("index= %i\n", index);

    printf("Array After update operation\n");
    ArrType c = Update_element_at_Array(&b, 100, 2);
    Traverse_over_Array(&c);
}

//functions
//Traverse Operation
void Traverse_over_Array(ArrType *arr)
{
    int i;
    printf("***************\n");
    for (i = 0; i < arr->len; i++)
        printf("array[%i]=%i\n", i, arr->arr[i]);
    printf("***************\n");
}
// Insertion Operation
ArrType insert_element_intoArray(ArrType *arr, int element_to_insert, int at_index)
{
    // printf("\ninside received address = %p inside length=%lu\n", arr->arr, arr->len);
    int working_array[100] = {0};
    memcpy(working_array, arr->arr, arr->len * sizeof(int));

    int i = arr->len - 1;

    while (i >= at_index)
    {
        // printf("working_array[%i]=%i -> working_array[%i]=%i \n", i, working_array[i], (i + 1), working_array[i + 1]);
        working_array[i + 1] = working_array[i];
        i = i - 1;
    }

    working_array[at_index] = element_to_insert;

    ArrType new_Array;
    new_Array.arr = working_array;
    new_Array.len = arr->len + 1;

    return new_Array;
}
//Deletion Operation
ArrType Delete_element_fromArray(ArrType *arr, int at_index)
{
    int i = at_index;

    while (i < (arr->len))
    {
        // printf("working_array[%i]=%i -> working_array[%i]=%i \n", i + 1, arr->arr[i + 1], (i), arr->arr[i]);
        arr->arr[i] = arr->arr[i + 1];
        i = i + 1;
    }

    arr->len = arr->len - 1;

    return *arr;
}
//Search Operation
int Search_in_Array(ArrType *arr, int search_for_this_item)
{
    int i;
    for (i = 0; i < arr->len; i++)
        if (arr->arr[i] == search_for_this_item)
            return i;
    return -1;
}
//Update Operation
ArrType Update_element_at_Array(ArrType *arr, int value_to_update, int at_index)
{
    arr->arr[at_index] = value_to_update;
    return *arr;
}
