#include <stdio.h>

void fizzBuzz(int n);

void main()
{
    fizzBuzz(15);
}

void fizzBuzz(int n)
{
    for (int i = 1; i <= n; i++)
    {
        char s[10];

        if ((i % 3 == 0) && (i % 5 == 0))
            printf("FizzBuzz");
        else if ((i % 3 == 0))
            printf("Fizz");
        else if ((i % 5 == 0))
            printf("Buzz");
        else
            printf("%i", i);
        printf("\n");
    }
}