#include <stdio.h>

int factorial(int n)
{
    int fact = 1;
    for (int i = n; i > 0; i--)
        fact *= i;

    return fact;
}

int fibbonacci(int n)
{
    // int f[n + 2];
    // int i;

    // // 0th and 1st number of the
    // // series are 0 and 1
    // f[0] = 0;
    // f[1] = 1;

    // int fib = 0;
    // if (n == 1)
    //     fib = 1;

    // for (int i = 2; i <= n; i++)
    //     f[i] = f[i - 1] + f[i - 2];

    // return f[n];

    int a = 0, b = 1, c, i;
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

int main()
{
    int n = 5;
    int i;

    printf("Factorial of %d: %d\n", n, factorial(n));
    printf("Fibbonacci of %d: ", n);

    n = 10;
    for (i = 0; i < n; i++)
        printf("%d ", fibbonacci(i));
    printf("\n");
}