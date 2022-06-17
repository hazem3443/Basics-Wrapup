#include <stdio.h>
#include <stdlib.h>

int array_intersection(int *arr1, int *arr2, int arr1_size, int arr2_size);

int main()
{
    int nums1[] = {1,2,2,1}, nums2[] = {2,2};

    array_intersection(nums1,nums2,4,2);    

    int nums_2_1[] = {4,9,5}, nums_2_2[] = {9,4,9,8,4};

    array_intersection(nums_2_1,nums_2_2,3,5);

    return 0;
}

int array_intersection(int *arr1, int *arr2, int arr1_size, int arr2_size)
{
    int i, j, k;
    int *result = (int *)malloc(sizeof(int) * (arr1_size + arr2_size));
    int result_size = 0;
    for (i = 0; i < arr1_size; i++)
    {
        for (j = 0; j < arr2_size; j++)
        {
            if (arr1[i] == arr2[j])
            {
                result[result_size] = arr1[i];
                result_size++;
                break;
            }
        }
    }
    for (k = 0; k < result_size; k++)
    {
        printf("%d ", result[k]);
    }
    printf("\n");
    return 0;
}