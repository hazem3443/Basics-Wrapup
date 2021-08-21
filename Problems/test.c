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
    printf("A val = %i, str = %c\n", instance1[0].x, instance1[0].y);
    printf("B val = %i, str = %c\n", instance1[1].x, instance1[1].y);
    printf("C val = %i, str = %c\n", instance1[2].x, instance1[2].y);
}