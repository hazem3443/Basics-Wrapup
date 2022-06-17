#include <stdio.h>
#include <stdlib.h>

int find_first_NonRepeat_element(int* arr, int n);

int main()
{
    printf("Hello world!\n");

    int arr1[] = {4,-1,2,-1,2};
    int x1 = find_first_NonRepeat_element(arr1, 5);
    printf("res 1 = %d\n", x1);

    int arr2[] = {2,2,1};
    int x2 = find_first_NonRepeat_element(arr2, 3);
    printf("res 2 = %d\n", x2);

    int arr3[] = {1};
    int x3 = find_first_NonRepeat_element(arr3, 1);
    printf("res 3 = %d\n", x3);
    return 0;
}

//remove repeated elements from an array
int find_first_NonRepeat_element(int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n; j++)
            if (i != j && arr[i] == arr[j])
                break;
        if (j == n)
            return arr[i];
    }
    return -1;
}
