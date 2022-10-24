#include <stdio.h>

int* sortedSquares(int* nums, int numsSize, int* returnSize);
void countingsort(int* arr, unsigned int arrsize);

void main(){
    int nums[] = {-2,-1,0,3};
    int* pnums;
    int pnums_len;
    pnums = sortedSquares(nums, (int)sizeof(nums)/sizeof(int), &pnums_len);
    
    for (size_t i = 0; i < pnums_len; i++)
    {
        printf("%d ,", pnums[i]);
    }
}

int* sortedSquares(int* nums, int numsSize, int* returnSize){
    for (size_t i = 0; i < numsSize; i++)
        nums[i]*=nums[i];

    countingsort(nums, numsSize);
    
    *returnSize = numsSize;
    return nums;
}

void countingsort(int* arr, unsigned int arrsize){
    // counting sort
    int max=0;
    int min=0;
    // finding max element
    for (size_t i = 0; i < arrsize; i++){
        if(arr[i]>max) max=arr[i];
        if(arr[i]<min) min=arr[i];
    }
    // allocating memory to count array
    int count[(max-min)+1];
    // initializing count array with all zero
    for (size_t i = 0; i <= max; i++) count[i]=0;
    // increasing the occurence of the number of "number" element
    for (size_t i = 0; i < arrsize; i++) count[arr[i]-min]++;
    // adding the previous count
    for (size_t i = 1; i <= max; i++)   count[i]+=count[i-1];
    // now storing the elements at their respective indexes
    int p[arrsize];
    for (size_t i = 0; i < arrsize; i++)
        p[--count[arr[i]]] = arr[i];

    for (size_t i = 0; i < arrsize; i++)
        arr[i]=p[i];
    

}