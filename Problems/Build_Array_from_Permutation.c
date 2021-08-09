#include <stdio.h>
#include <stdlib.h>

int *buildArray(int *nums, int numsSize, int *returnSize);
void print_arr(int *nums, int numsSize);

void main()
{
    int nums[] = {0, 2, 1, 5, 3, 4};
    print_arr(nums, 6);

    int *ret;
    buildArray(nums, 6, ret);

    print_arr(nums, 6);
}

// int *buildArray(int *nums, int numsSize, int *returnSize)
// {
//     int *malloc_ptr = malloc(sizeof(int) * numsSize);

//     for (int i = 0; i < numsSize; i++)
//     {
//         malloc_ptr[i] = nums[nums[i]];
//     }

//     returnSize = malloc_ptr;
//     return returnSize;
// }

int *buildArray(int *nums, int numsSize, int *returnSize)
{
    int i;
    // *returnSize = numsSize;

    for (i = 0; i < numsSize; i++)
    {
        nums[i] = (nums[nums[i] % numsSize] % numsSize) * numsSize + nums[i];
    }
    print_arr(nums, 6);

    for (i = 0; i < numsSize; i++)
    {
        nums[i] = nums[i] / numsSize;
    }
    return nums;
}

void print_arr(int *nums, int numsSize)
{
    printf("[");
    for (int i = 0; i < numsSize; i++)
        printf(" %i,", nums[i]);
    printf("\b ]");
}