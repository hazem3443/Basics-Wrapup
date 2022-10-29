

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

void merge(int* arr, int left, int middle, int right);
void mergeSort(int* arr, int left, int right);
void merge_sort(int *arr, int N);
void swap(int *x, int*y);

int* sortedSquares(int* nums, int numsSize, int* returnSize);

int* sortedSquares(int* nums, int numsSize, int* returnSize){
    for (size_t i = 0; i < numsSize; i++)
        nums[i]*=nums[i];
    
    merge_sort(nums, numsSize);
    *returnSize=numsSize;
    return nums;
}
void merge(int* arr, int left, int middle, int right){
    int i, j, k;
    int Lsize = middle-left+1;
    int Rsize = right-middle;
    int L[Lsize];
    int R[Rsize];
    for ( i = 0; i < Lsize; i++) L[i] = arr[left+i];
    for ( j = 0; j < Rsize; j++) R[j] = arr[middle+1+j];
    
    i=0, j=0, k=left;

    while (i < Lsize && j<Rsize){
        if(L[i]<=R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i<Lsize) arr[k++] = L[i++];
    while (j<Rsize) arr[k++] = R[j++];
    
}
void mergeSort(int* arr, int left, int right){
    
    if (right > left){
        int middle = left + (right-left)/2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}
void merge_sort(int *arr, int N){
    mergeSort(arr, 0, N-1);
}

int main(){
    int arr[] = {-4,-1,0,3,10};
    int N = sizeof(arr)/sizeof(arr[0]);
    int returnSize;
    int *res = sortedSquares(arr, N, &returnSize);
    for (size_t i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
}

// int* sortedSquares(int* nums, int numsSize, int* returnSize){
//     int *res = (int*)malloc(numsSize*sizeof(int));
//     int i=0, j=numsSize-1, k=numsSize-1;
//     while (i<=j){
//         if (nums[i]*nums[i] > nums[j]*nums[j]){
//             res[k--] = nums[i]*nums[i];
//             i++;
//         }
//         else{
//             res[k--] = nums[j]*nums[j];
//             j--;
//         }
//     }
//     *returnSize = numsSize;
//     return res;
// }