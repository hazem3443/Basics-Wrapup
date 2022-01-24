#include <stdio.h>
#include <stdbool.h>

int lonelyinteger(int a_count, int *a);

void main()
{
    int a[] = {34, 95, 34, 64, 45, 95, 16, 80, 80, 75, 3, 25, 75, 25, 31, 3, 64, 16, 31};

    int a_count = 19;
    printf("Hellow World %i \n", lonelyinteger(a_count, a));
}

int lonelyinteger(int a_count, int *a)
{
    bool arr[100] = {0};
    for (int i = 0; i < a_count; i++)
    {
        arr[a[i]] ^= 1;
        // printf("a[%i]=%i, arr[%i]=%i\n", i, a[i], a[i], arr[a[i]]);
    }
    int res = 0;
    for (res = 0; res < 100; res++)
    {
        if (arr[res] == 1)
            break;
    }
    return res;
}