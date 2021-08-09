#include <stdio.h>
#include <stdlib.h>

int *getConcatenation(int *nums, int numsSize, int *returnSize);
void print_arr(int *nums, int numsSize);

void main()
{
    int nums[] = {1, 2, 1};
    print_arr(nums, 3);
    printf("\n");

    int rsi;

    int *new_arr;
    new_arr = getConcatenation(nums, 3, &rsi);
    printf("\n");
    print_arr(new_arr, 6);

    free(new_arr);
}

int *getConcatenation(int *nums, int numsSize, int *returnSize)
{
    *returnSize = numsSize * 2;
    int *ptr = malloc(numsSize * 2 * sizeof(int));
    for (int i = 0; i < numsSize; i++)
    {
        ptr[i] = nums[i];
        ptr[i + numsSize] = nums[i];
    }
    return ptr;
}

void print_arr(int *nums, int numsSize)
{
    printf("[");
    for (int i = 0; i < numsSize; i++)
        printf(" %i,", nums[i]);
    printf("\b ]");
}