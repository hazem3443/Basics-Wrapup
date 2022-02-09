#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    for (int i = 0; i < 9; i++)
    {
        printf("Hellow %i\n", *(*(arr + i) + i));
    }
}