#include <stdio.h>
#include <stdlib.h>

int diagonalDifference(int arr_rows, int arr_columns, int **arr);

void main()
{
    int disp1[3][3] = {{1, 2, 3}, {4, 5, 6}, {9, 8, 9}};     // res=2
    int disp2[3][3] = {{11, 2, 4}, {4, 5, 6}, {10, 8, -12}}; // res=15

    int i, j;

    int **arr = malloc(3 * sizeof(int *));

    for (i = 0; i < 3; i++)
    {
        *(arr + i) = malloc(3 * (sizeof(int)));
        for (j = 0; j < 3; j++)
        {
            *(*(arr + i) + j) = disp1[i][j];
        }
    }

    printf("res = %i\n", diagonalDifference(3, 3, arr));

    for (i = 0; i < 3; i++)
    {
        *(arr + i) = malloc(3 * (sizeof(int)));
        for (j = 0; j < 3; j++)
        {
            *(*(arr + i) + j) = disp2[i][j];
        }
    }

    printf("res = %i\n", diagonalDifference(3, 3, arr));
}

int diagonalDifference(int arr_rows, int arr_columns, int **arr)
{
    int x_ltr = 0;
    // left to right diag
    for (int i = 0; i < arr_rows; i++)
    {
        x_ltr += arr[i][i];
    }

    int x_rtl = 0;
    // right to left diag
    for (int i = 0, j = arr_columns; (i < arr_rows) && (j > 0); i++, j--)
    {
        x_rtl += arr[i][j - 1];
    }
    return abs(x_ltr - x_rtl);
}
