//starts at 9.06
//reading ends at 9.16
//solving ends at
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(int *arr, int arrSize, int d, int *dp, int idx);
int maxJumps(int *arr, int arrSize, int d);
int max(int num1, int num2);

void main()
{
    int arr[] = {6, 4, 14, 6, 8, 13, 9, 7, 10, 6, 12};
    int d = 2;
    int res = maxJumps(arr, sizeof(arr) / sizeof(int), d);
    printf("Test case %s res=%i\n", res == 4 ? "Passed" : "Failed", res);

    int arr2[] = {3, 3, 3, 3, 3};
    d = 3;
    res = maxJumps(arr2, sizeof(arr2) / sizeof(int), d);
    printf("Test case %s\n", res == 1 ? "Passed" : "Failed");

    int arr3[] = {7, 6, 5, 4, 3, 2, 1};
    d = 1;
    res = maxJumps(arr3, sizeof(arr3) / sizeof(int), d);
    printf("Test case %s\n", res == 7 ? "Passed" : "Failed");

    int arr4[] = {7, 1, 7, 1, 7, 1};
    d = 2;
    res = maxJumps(arr4, sizeof(arr4) / sizeof(int), d);
    printf("Test case %s\n", res == 2 ? "Passed" : "Failed");

    int arr5[] = {66};
    d = 1;
    res = maxJumps(arr5, sizeof(arr5) / sizeof(int), d);
    printf("Test case %s\n", res == 1 ? "Passed" : "Failed");
    // printf("hellow world %li\n", sizeof(arr) / sizeof(int));
}

int maxJumps(int *arr, int arrSize, int d)
{
    int res = 1;

    int *dp[arrSize];
    for (int i = 0; i < arrSize; i++)
    {
        dp[i] = (int *)malloc(sizeof(int)); // = {-1};
        *(dp[i]) = -1;
    }
    // printf("\n$0 size = %li\n", (sizeof(dp) / sizeof(int *)));

    for (int i = 0; i < arrSize; ++i)
        res = max(res, f(arr, arrSize, d, *dp, i));
    return res;
    // int max_sum = 0;
    // for (int i = arrSize - 1; i >= 0; i--)
    // {
    //     int current_jump = 0;
    //     for (j = d; j >= 0; j--)
    //     {
    //         if (arr[i] > arr[j])
    //             current_jump = ;
    //     }
    //     j = d;
    // }
}

int f(int *arr, int arrSize, int d, int *dp, int idx)
{
    //if cached, return cached result
    if (dp[idx] > -1)
        return dp[idx];

    int l = idx, r = idx, m = 0;
    //figure out left and right bound
    while (l > 0 && arr[l - 1] < arr[idx] && (idx - l) < d)
        --l;
    while (r < arrSize - 1 && arr[r + 1] < arr[idx] && (r - idx) < d)
        ++r;

    for (int i = l; i <= r; ++i)
    {
        if (i == idx)
            continue;
        m = max(m, f(arr, arrSize, d, dp, i));
    }
    //write cache
    return dp[idx] = m + 1;
}

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}
