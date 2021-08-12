#include <stdio.h>

unsigned long int fibbonacci_memo(int n, unsigned long int *memo)
{
    if (memo[n] != 0)
        return memo[n];

    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        memo[n] = (fibbonacci_memo(n - 1, memo) + fibbonacci_memo(n - 2, memo));
        return memo[n];
    }
}

unsigned long int fibbonacci(int n)
{ //fibonacci iteratively
    unsigned long int a = 0, b = 1, c, i;
    if (n == 0)
        return a;
    for (i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

unsigned long int fibbonacci_tabulation(int n)
{
    if (n == 0)
        return 0;
    unsigned long int arr[n + 1];
    int i;
    for (i = 0; i < n + 1; i++)
        arr[i] = 0;

    arr[1] = 1;
    for (i = 0; i <= n; i++)
    {
        arr[i + 1] += arr[i];
        arr[i + 2] += arr[i];
    }

    return arr[n];
}
int main()
{
    int n = 50;
    int i;
    unsigned long int gmemo[100] = {0};

    printf("Fibbonacci of %d: %li \n", n, fibbonacci_memo(n, gmemo));
    printf("Fibbonacci of %d: %li \n", n, fibbonacci(n));
    printf("Fibbonacci of %d: %li \n", n, fibbonacci_tabulation(n));
}