#include <stdio.h>

void duplicateZeros(int* arr, int arrSize);

int main() {
    int arr[] = {1, 0, 2, 3, 0, 4, 5, 0};

    duplicateZeros(arr, 8);

    // for (int i = 0; i < 8; i++) {
    //     printf("%d ", arr[i]);
    // }

    int arr2[] = {0,4,1,0,0,8,0,0,3};
    duplicateZeros(arr2, 9);
    for (int i = 0; i < 9; i++) {
        printf("%d ", arr2[i]);
    }
    return 0;
}


void duplicateZeros(int* arr, int arrSize){
    int i,j;
    for(i=0;i<arrSize-1;i++){
        if( (arr[i]==0) ){
            // insert 0 at index=i+1
            for(j = arrSize-1 ;j>i;j--){
                arr[j]=arr[j-1];
            }
            // arr[j]=0;
            i++;
        }
    }
}