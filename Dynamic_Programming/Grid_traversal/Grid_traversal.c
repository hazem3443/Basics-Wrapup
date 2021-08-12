#include <stdio.h>

unsigned long int grid_traversal(int m, int n);
unsigned long int grid_traversal_memo(int m, int n, unsigned long int *memo);
unsigned long int grid_traversal_Tabulation(int m, int n);

void print(int *arr, int m, int n);

int main()
{
    unsigned long int memo[100][100] = {{0}};

    printf("Grid Traversal Routes of %d x %d grid: %li \n", 1, 1, grid_traversal(1, 1));                                                 //1
    printf("Grid Traversal Routes of %d x %d grid: %li \n", 2, 3, grid_traversal(2, 3));                                                 //3
    printf("Grid Traversal Routes of %d x %d grid: %li \n", 3, 2, grid_traversal(3, 2));                                                 //3
    printf("Grid Traversal Routes of %d x %d grid: %li \n", 3, 3, grid_traversal(3, 3));                                                 //6
    printf("Grid Traversal Memoizingly Routes of %d x %d grid: %li \n", 18, 18, grid_traversal_memo(18, 18, (unsigned long int *)memo)); //2333606220

    printf("Grid Traversal Tabulationly Routes of %d x %d grid: %li \n", 18, 18, grid_traversal_Tabulation(18, 18)); //2333606220
    // int arr[3][3] = {{0}};
    // print((int *)arr, 3, 3);
}

unsigned long int grid_traversal(int m, int n)
{
    if (m == 1 && n == 1)
        return 1;
    if (m == 0 || n == 0)
        return 0;

    return grid_traversal(m - 1, n) + grid_traversal(m, n - 1);
}

//with memoization
unsigned long int grid_traversal_memo(int m, int n, unsigned long int *memo)
{
    if (*((memo + (m * 100)) + n) != 0 || *((memo + (n * 100)) + m) != 0)
        return *((memo + (m * 100)) + n);

    if (m == 1 && n == 1)
        return 1;
    if (m == 0 || n == 0)
        return 0;

    *((memo + (m * 100)) + n) = grid_traversal_memo(m - 1, n, (unsigned long int *)memo) + grid_traversal_memo(m, n - 1, (unsigned long int *)memo);
    *((memo + (n * 100)) + m) = *((memo + (m * 100)) + n);
    return *((memo + (m * 100)) + n);
}

unsigned long int grid_traversal_Tabulation(int m, int n)
{
    unsigned long int arr[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            arr[i][j] = 0;

    arr[1][1] = 1;

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
        {
            unsigned long int current = arr[i][j];
            if (j + 1 <= n)
                arr[i][j + 1] += current;
            if (i + 1 <= m)
                arr[i + 1][j] += current;
        }

    // for (int i = 0; i <= m; i++)
    // {
    //     printf("{[");

    //     for (int j = 0; j <= n; j++)
    //     {
    //         printf("%li, ", arr[i][j]);
    //     }
    //     printf("\b\b],\n");
    // }
    return arr[m][n];
}
