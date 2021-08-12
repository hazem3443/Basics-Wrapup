#include <stdio.h>

int str_length(char *str);
void swap(char *x, char *y);
void reverse_str(char *str, char *rev, int strlen);

void main()
{
    char *s = "geeksforgeeks";
    int i = str_length(s);
    char rev[i];
    reverse_str(s, rev, i);

    printf("before reverse = %s\n", s);
    printf("after  reverse = %s\n", rev);
}

void reverse_str(char *str, char *rev, int strlen)
{
    for (int i = 0; i < (strlen / 2); i++)
    {
        rev[strlen - i - 1] = str[i];
        rev[i] = str[strlen - i - 1];
    }

    if (strlen % 2 != 0)
        rev[((strlen + 1) / 2) - 1] = str[((strlen + 1) / 2) - 1];

    rev[strlen] = '\0';
}
int str_length(char *str)
{
    int i = 0;
    while (str[++i] != '\0')
        ;
    return i;
}
void swap(char *x, char *y)
{
    printf("%c ---Xaddr = %p\n", *x, x);
    char temp = *x;
    printf("%c ---Yaddr = %p\n", *y, y);
    *x = *y;
    *y = temp;
}