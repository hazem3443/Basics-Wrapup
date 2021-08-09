//start at 10.30
//reading 10.31 ends 10.45
//solved at
//submitted at
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cols;

int connected_faces(int *grid[cols], int rows, int *comls, int i, int j);
int calc_SA_tower(int num);
int surfaceArea(int *grid[cols], int gridSize, int *gridColSize);

void print_arr(int *nums, int numsSize);

void array_pass(int **grid, int row, int col);

void main()
{
    int gridColSize = 1;
    int gridSize = 1;
    int *grid[gridSize];

    for (int i = 0; i < gridSize; i++)
        grid[i] = (int *)malloc(gridColSize * sizeof(int));

    grid[0][0] = 2;

    // int *grid = (int **)malloc(sizeof(int) * array_size);
    // grid[0][0] = 2;
    int res = surfaceArea(grid, gridSize, &gridColSize);

    printf("Test Case 1 %s OUT = %i\n", ((res == 10) ? "Passed" : "Failed"), res);

    gridColSize = 2;
    gridSize = 2;
    *grid[gridSize];

    for (int i = 0; i < gridSize; i++)
        grid[i] = (int *)malloc(gridColSize * sizeof(int));

    grid[0][0] = 1;
    grid[0][1] = 2;
    grid[1][0] = 3;
    grid[1][1] = 4;

    // int *grid = (int **)malloc(sizeof(int) * array_size);
    // grid[0][0] = 2;
    res = surfaceArea(grid, gridSize, &gridColSize);

    printf("Test Case 2 %s OUT = %i\n", ((res == 34) ? "Passed" : "Failed"), res);

    gridColSize = 2;
    gridSize = 2;
    *grid[gridSize];

    for (int i = 0; i < gridSize; i++)
        grid[i] = (int *)malloc(gridColSize * sizeof(int));

    grid[0][0] = 1;
    grid[0][1] = 0;
    grid[1][0] = 0;
    grid[1][1] = 2;

    // int *grid = (int **)malloc(sizeof(int) * array_size);
    // grid[0][0] = 2;
    res = surfaceArea(grid, gridSize, &gridColSize);

    printf("Test Case 3 %s OUT = %i\n", ((res == 16) ? "Passed" : "Failed"), res);

    gridColSize = 3;
    gridSize = 3;
    *grid[gridSize];

    for (int i = 0; i < gridSize; i++)
        grid[i] = (int *)malloc(gridColSize * sizeof(int));

    // {{1,1,1},{1,0,1},{1,1,1}}

    grid[0][0] = 1;
    grid[0][1] = 1;
    grid[0][2] = 1;
    grid[1][0] = 1;
    grid[1][1] = 0;
    grid[1][2] = 1;
    grid[2][0] = 1;
    grid[2][1] = 1;
    grid[2][2] = 1;
    // int *grid = (int **)malloc(sizeof(int) * array_size);
    // grid[0][0] = 2;
    res = surfaceArea(grid, gridSize, &gridColSize);

    printf("Test Case 4 %s OUT = %i\n", ((res == 32) ? "Passed" : "Failed"), res);
    // [[2,2,2],[2,1,2],[2,2,2]]
}

int surfaceArea(int *grid[cols], int gridSize, int *gridColSize)
{
    int res = 0;
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < *gridColSize; j++)
        {
            res += calc_SA_tower(grid[i][j]) - connected_faces(grid, gridSize, gridColSize, i, j);
        }
    }
    return res;
}

int calc_SA_tower(int num)
{
    return (num * 6) - (((num - 1) > 0 ? (num - 1) : 0) * 2);
}

int connected_faces(int *grid[cols], int rows, int *comls, int i, int j)
{
    //horizontal
    int mod_i = i, mod_j = j, faces_sum = 0;

    if (mod_i < rows - 1) //down
    {
        if (grid[++mod_i][j] > grid[i][j])
            faces_sum += grid[i][j];
        else
            faces_sum += grid[mod_i][j];

        mod_i = mod_i - 2;
    }
    else
        mod_i--;

    if (mod_i >= 0) //up
    {
        if (grid[mod_i][j] > grid[i][j])
            faces_sum += grid[i][j];
        else
            faces_sum += grid[mod_i][j];
    }

    if (mod_j < *comls - 1) //right
    {
        if (grid[i][++mod_j] > grid[i][j])
            faces_sum += grid[i][j];
        else
            faces_sum += grid[i][mod_j];

        mod_j = mod_j - 2;
    }
    else
        mod_j--;

    if (mod_j >= 0) //left
    {
        if (grid[i][mod_j] > grid[i][j])
            faces_sum += grid[i][j];
        else
            faces_sum += grid[i][mod_j];
    }
    // printf("grid[%i][%i] = %i is %i calc_SA_tower =%i \n ", i, j, grid[i][j], faces_sum, calc_SA_tower(grid[i][j]));
    return faces_sum;
}

void print_arr(int *nums, int numsSize)
{
    printf("[");
    for (int i = 0; i < numsSize; i++)
        printf(" %i,", nums[i]);
    printf("\b ]");
}