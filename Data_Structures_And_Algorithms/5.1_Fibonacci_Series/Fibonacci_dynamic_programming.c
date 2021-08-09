#include <stdio.h>

unsigned long int fibbonacci(int n, unsigned long int *memo)
{
    if (memo[n] != 0)
        return memo[n];

    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        memo[n] = (fibbonacci(n - 1, memo) + fibbonacci(n - 2, memo));
        return (fibbonacci(n - 1, memo) + fibbonacci(n - 2, memo));
    }
}

int main()
{
    int n = 50;
    int i;
    unsigned long int gmemo[100] = {0};

    printf("Fibbonacci of %d: %li \n", n, fibbonacci(n, gmemo));
}