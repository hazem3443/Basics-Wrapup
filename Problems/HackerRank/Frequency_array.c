#include <stdio.h>
#include <stdlib.h>

int *countingSort(int arr_count, int *arr, int *result_count);

void main()
{
    int n = 100;
    int arr[] = {63, 25, 73, 1, 98, 73, 56, 84, 86, 57, 16, 83, 8, 25, 81, 56, 9, 53, 98, 67, 99, 12, 83, 89, 80, 91, 39, 86, 76, 85, 74, 39, 25, 90, 59, 10, 94, 32, 44, 3, 89, 30, 27, 79, 46, 96, 27, 32, 18, 21, 92, 69, 81, 40, 40, 34, 68, 78, 24, 87, 42, 69, 23, 41, 78, 22, 6, 90, 99, 89, 50, 30, 20, 1, 43, 3, 70, 95, 33, 46, 44, 9, 69, 48, 33, 60, 65, 16, 82, 67, 61, 32, 21, 79, 75, 75, 13, 87, 70, 33};
    int res_count;

    int i = 0;
    for (i = 0; arr[i] != '\0'; i++)
        ;
    int len = i - 1;

    int *res_arr = countingSort(len, arr, &res_count);

    for (i = 0; i < res_count; i++)
        printf("%i ", res_arr[i]);

    int countsum = 0;
    for (i = 0; i < len; i++)
        while (res_arr[i] != 0)
        {
            arr[i] += i--;
        }

    printf("\n%i\n", countsum);
}

int *countingSort(int arr_count, int *arr, int *result_count)
{
    int *res_arr = calloc(100, sizeof(int));

    for (int i = 0; i < arr_count; i++)
    {
        res_arr[arr[i]]++;
    }
    *result_count = 100;
    return res_arr;
}