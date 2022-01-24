#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int flippingMatrix(int matrix_rows, int matrix_columns, int **matrix);
int main()
{

    int n;
    scanf("%d", &n);
    int matrix[2 * n][2 * n];
    int sol[2 * n][2 * n];

    for (int i = 0; i < 2 * n; i++)
    {

        for (int j = 0; j < 2 * n; j++)
        {
            scanf("%d", &matrix[i][j]);
            sol[i][j] = 0;
        }
    }

    int sum = flippingMatrix(n * 2, n * 2, matrix);
    printf("%d\n", sum);

    return 0;
}

int flippingMatrix(int matrix_rows, int matrix_columns, int **matrix)
{
    int sum = 0;
    int n = (matrix_rows / 2);
    int sol[2 * n][2 * n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a = matrix[i][j];
            if (matrix[2 * n - 1 - i][2 * n - 1 - j] > a && sol[2 * n - 1 - i][2 * n - 1 - j] == 0)
            {
                a = matrix[2 * n - 1 - i][2 * n - 1 - j];
                sol[2 * n - 1 - i][2 * n - 1 - j]++;
            }
            if (matrix[i][2 * n - 1 - j] > a && sol[i][2 * n - 1 - j] == 0)
            {
                a = matrix[i][2 * n - 1 - j];
                sol[i][2 * n - 1 - j]++;
            }
            if (matrix[2 * n - 1 - i][j] > a && sol[2 * n - 1 - i][j] == 0)
            {
                a = matrix[2 * n - 1 - i][j];
                sol[2 * n - 1 - i][j]++;
            }
            sum += a;
        }
    }
    return sum;
}