#include <stdio.h>

int x = 10;
int y = 11;

struct m
{
    int x;
    char y;
};

struct m instance1[] = {
    {.x = 1, .y = 'A'},
    {.x = 2, .y = 'B'},
    {.x = 3, .y = 'C'}};

void main()
{

    printf("hellow world\n");
    // printf("A val = %i, str = %c\n", instance1[0].x, instance1[0].y);
    // printf("B val = %i, str = %c\n", instance1[1].x, instance1[1].y);
    // printf("C val = %i, str = %c\n", instance1[2].x, instance1[2].y);

    int x[20] = {0};

    //    10*10 matrix

    // array of n elements can be defined as i*j matrix where i*j=n
    // we can access matrix[i][j] by step shifting as follows
    //   *(x + i + (j << row_size-1)) = value;
    // we must deal with even number of row sizes

    *(x + (2 << 2) + 0) = 5;
    for (int i = 0; i < 20; i++)
    {
        if (i % 4 == 0 && i != 0)
            printf("\n");
        printf("%i ", x[i]);
    }
    printf("\n");
}