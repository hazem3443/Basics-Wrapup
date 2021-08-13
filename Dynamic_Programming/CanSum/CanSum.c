#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canSum(int n, int *arr, int arrlen);
bool canSum_memoized(int targetSum, int *arr, int arrlen, int *memo);
bool canSum_Tabulation(int targetSum, int *arr, int arrlen);

void main()
{

    int arr[] = {2, 3};
    int arr1[] = {5, 3, 4, 7};
    int arr2[] = {2, 4};
    int arr3[] = {2, 3, 5};
    int arr4[] = {7, 14};

    printf("target = 7 arr = [2, 3] res = %s\n", canSum(7, arr, sizeof(arr) / sizeof(int)) ? "True" : "False");
    printf("target = 7 arr = [5, 3, 4, 7] res = %s\n", canSum(7, arr1, sizeof(arr1) / sizeof(int)) ? "True" : "False");
    printf("target = 7 arr = [2, 4] res = %s\n", canSum(7, arr2, sizeof(arr2) / sizeof(int)) ? "True" : "False");
    printf("target = 8 arr = [2, 3, 5] res = %s\n", canSum(8, arr3, sizeof(arr3) / sizeof(int)) ? "True" : "False");
    // printf("target = 300 arr = [7, 14] res = %s\n", canSum(300, arr4, sizeof(arr4) / sizeof(int)) ? "True" : "False");
    // True
    // True
    // False
    // True
    // False

    int memo[1000] = {3};
    // printf("target = 300 arr = [7, 14] res = %s\n", canSum_memoized(300, arr4, sizeof(arr4) / sizeof(int), memo) ? "True" : "False");
    printf("Tabulation Test Cases\n");
    printf("target = 7 arr = [2, 3] res = %s\n", canSum_Tabulation(7, arr, sizeof(arr) / sizeof(int)) ? "True" : "False");
    printf("target = 7 arr = [5, 3, 4, 7] res = %s\n", canSum_Tabulation(7, arr1, sizeof(arr1) / sizeof(int)) ? "True" : "False");
    printf("target = 7 arr = [2, 4] res = %s\n", canSum_Tabulation(7, arr2, sizeof(arr2) / sizeof(int)) ? "True" : "False");
    printf("target = 8 arr = [2, 3, 5] res = %s\n", canSum_Tabulation(8, arr3, sizeof(arr3) / sizeof(int)) ? "True" : "False");
    printf("target = 300 arr = [7, 14] res = %s\n", canSum_Tabulation(300, arr4, sizeof(arr4) / sizeof(int)) ? "True" : "False");
}

bool canSum(int targetSum, int *arr, int arrlen)
{
    if (targetSum == 0)
        return true;
    if (targetSum < 0)
        return false;

    for (int i = 0; i < arrlen; i++)
    {
        if (canSum(targetSum - arr[i], arr, arrlen) == true)
        {
            return true;
        }
        // printf("%i\n", arr[i]);
    }
    return false;
}

bool canSum_memoized(int targetSum, int *arr, int arrlen, int *memo)
{
    if (memo[targetSum] != 3)
        return memo[targetSum];
    if (targetSum == 0)
    {
        memo[targetSum] = true;
        return memo[targetSum];
    }
    if (targetSum < 0)
    {
        memo[targetSum] = false;
        return memo[targetSum];
    }

    for (int i = 0; i < arrlen; i++)
    {
        if (canSum_memoized(targetSum - arr[i], arr, arrlen, memo) == true)
        {
            memo[targetSum] = true;
            return memo[targetSum];
        }
        // printf("%i\n", arr[i]);
    }
    memo[targetSum] = false;
    return memo[targetSum];
}

bool canSum_Tabulation(int targetSum, int *arr, int arrlen)
{
    bool newArr[targetSum + 1];

    for (int i = 0; i <= targetSum; i++)
        newArr[i] = false;

    newArr[0] = true;
    for (int i = 0; i <= targetSum; i++)
    {
        if (newArr[i] == true)
        {
            for (int j = 0; j < arrlen; j++)
                newArr[i + arr[j]] = true;
        }
    }
    return newArr[targetSum];
}