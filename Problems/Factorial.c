#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fact(int x);
int multiply(int x, int y);

void main()
{
    // printf("Hellow World fact %i\n", fact(5));
    // printf("Hellow World multiply %i\n", multiply(5, 10));

    // int i = 4, j = 1;
    // int x = j || (i++) && 1;
    // // int *p = ;
    // printf("Hellow World multiply x= %i , i = %i\n", x, i);
    // // printf("Hellow x= %p\n", p);
    // printf("Hellow x= %i\n", *p);

    char str1[100000], str2[100000];

    int strnums = 0;

    scanf("%i", &strnums);

    int *p = malloc(strnums * sizeof(int));

    int k = 0;
    while (k < strnums)
    {
        // printf("Enter Text : ");
        scanf("%s", str1);

        // printf("Enter Pattern : ");
        scanf("%s", str2);

        int s1 = 0, s2 = 0;
        // printf("s1s2\n");
        while (str1[s1] != '\0')
        {
            if (str1[s1] == str2[s2])
            {
                int temps = s1;
                // printf("comp %c , %c\n", str1[s1], str2[s2]);

                while (str1[s1] != '\0' && str2[s2] != '\0' && str2[s2] == str1[s1])
                {
                    // printf("comp %c , %c\n", str1[s1], str2[s2]);
                    s2++;
                    s1++;
                }
                if (s2 == strlen(str2))
                {
                    *(p + k) = 1;
                    // printf()
                    break;
                }
                else
                {
                    *(p + k) = 0;
                }

                s1 = temps;
                s2 = 0;
            }
            s1++;
        }
        // printf("\nsize = %li, s2= %i \n", strlen(str2), s2);

        k++;
    }
    int l = 0;
    while (l < strnums)
    {
        // printf("\n%i", *(p + l));

        if (*(p + l))
            printf("YES\n");
        else
            printf("NO\n");
        l++;
    }

    // printf("\ns1\n");
}

int fact(int x)
{
    if (x == 1)
        return x;

    return x * fact(x - 1);
}
int multiply(int x, int y)
{
    if (y == 1)
        return x;

    return x + multiply(x, y - 1);
}
