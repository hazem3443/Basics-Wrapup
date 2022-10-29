#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);

int main(){

    int arr1[] = {1,2,3,0,0,0};
    int arr2[] = {2,5,6};
    merge(arr1, 6, 3, arr2, 3, 3);
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr1[i]);
    }

}
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    char i=0,j=0;
    int k=0;
    int* newarr = (int *)malloc(sizeof(int) * nums1Size);
    while(i<m && j< n){
        if(nums1[i]<nums2[j])
            newarr[k++]=nums1[i++];
        else
            newarr[k++]=nums2[j++];
    }
    
    while(i<m)newarr[k++]=nums1[i++];
    while(j<n)newarr[k++]=nums2[j++];
    
    memcpy(nums1, newarr, sizeof(int)*nums1Size);
    
    free(newarr);
}