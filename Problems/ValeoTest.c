#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int removeDuplicates(int *nums, int numsSize);
int find(int *arr, int numsSize, int data);
int maxProfit(int *prices, int pricesSize);

void SortBubbly(int *x, int len, bool asc);
void swapByReference(int *x, int *y);

void rotate(int *nums, int numsSize, int k);
int singleNumber(int *nums, int numsSize);

int *divide_merge(int *x, int len, bool asc);
int *merge(int *l1, int l1_len, int *l2, int l2_len, int *x, bool asc);
int *plusOne(int *digits, int digitsSize, int *returnSize);

void main()
{
    int returnSize = 0;
    int nums[] = {9, 9, 9};
    int numsSize = sizeof(nums) / sizeof(int);
    // rotate(nums, numsSize, 2);
    // divide_merge(nums, numsSize, 0);

    // printf("res = %i\n", singleNumber(nums, numsSize));
    printf("point");

    int *resarr = plusOne(nums, numsSize, &returnSize);
    printf("returnSize = %i\n", returnSize);
    for (int i = 0; i < returnSize; i++)
        printf("x[%i] = %i\n", i, resarr[i]);
}

int removeDuplicates(int *nums, int numsSize)
{
    int j = 1;
    for (int i = 0; i < numsSize - 1; i++)
    {
        if (nums[i] != nums[i + 1])
        {
            nums[j++] = nums[i + 1];
        }
    }
    return j;
}

int find(int *arr, int numsSize, int data)
{
    int lowerBound = 0;
    int upperBound = numsSize - 1;
    int midPoint = -1;

    while (lowerBound <= upperBound)
    {
        // midPoint = (lowerBound + upperBound) / 2;
        midPoint = lowerBound + (upperBound - lowerBound) / 2;

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

int maxProfit(int *prices, int pricesSize)
{
    int difs[pricesSize];
    for (int i = 0; i < pricesSize; i++)
        difs[i] = 0;
    for (int i = 0; i < pricesSize - 1; i++)
        difs[i] = prices[i + 1] - prices[i];

    SortBubbly(difs, pricesSize - 1, 0);
    for (int i = 0; i < pricesSize; i++)
    {
        printf("x = %i\n", difs[i]);
    }

    int res = 0;
    for (int i = 0; i < pricesSize; i++)
        if (difs[i] == 0)
            break;
        else if (difs[i] > 0)
            res += difs[i];

    return res;
}

void swapByReference(int *x, int *y)
{                 // O(3) -- S(0)
    *x = *y + *x; // x= x+y
    *y = *x - *y; // y = x+y-y = x
    *x = *x - *y; // x = x+y-x = y
}

void SortBubbly(int *x, int len, bool asc)
{
    for (size_t j = 0; j < len; j++)
    {
        for (size_t i = 0; i < len - j - 1; i++)
        {
            if (asc == 1)
            {
                if (x[i] > x[i + 1])
                    swapByReference(x + i, x + (i + 1));
            }
            else
            {
                if (x[i] < x[i + 1])
                    swapByReference(x + i, x + (i + 1));
            }
            // printf("arr[%lu] = %i\n", i, x[i]);
        }
        // printf("------\n");
    }
}

void rotate(int *nums, int numsSize, int k)
{
    for (int iter = 0; iter < k; iter++)
    {
        for (int i = numsSize - 2; i >= 0; i--)
        {
            swapByReference(nums + i, nums + i + 1);
        }
    }
}

int singleNumber(int *nums, int numsSize)
{
    SortBubbly(nums, numsSize, 0);
    for (int i = 0; i < numsSize; i++)
    {
        printf("x = %i\n", nums[i]);
        if (nums[i] != nums[i + 1] && i > 1 && nums[i - 1] != nums[i])
            return nums[i];
    }
    return nums[0];
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

    l1_len += l2_len;
    l2_len = 0;
    while ((x[l2_len] = l3[l2_len]) && ++l2_len < l1_len)
        ;

    free(l3);
    return x;
}

int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    *returnSize = digitsSize;
    int *ret_array;
    ret_array = (int *)malloc(*returnSize * sizeof(int));
    int flag = 0;
    for (int i = digitsSize - 1; i >= 0; i--)
    {
        printf("\ndig = %i\n", digits[i]);
        if (digits[i] == 9)
        {
            ret_array[i] = 0;
            if (i == 0)
            {
                printf("increm\n");
                flag = 1;
            }
            else
                continue;
        }
        else
        {
            printf("else %i\n", i);
            ret_array[i] = ++digits[i];
            while (i-- > 0)
                ret_array[i] = digits[i];

            break;
        }
    }
    if (flag == 1)
    {
        (*returnSize)++;
        ret_array = (int *)realloc(ret_array, (*returnSize * sizeof(int)));
        ret_array[((*returnSize) - 1)] = 1;
        swapByReference(ret_array, ret_array + *returnSize - 1);
    }

    return ret_array;
}