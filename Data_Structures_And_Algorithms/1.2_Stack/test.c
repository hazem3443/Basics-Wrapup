#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void main()
{
    int a = 54325;
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", a); // print int 'n' into the char[] buffer
    printf("Hexadecimal value = %s\n", buffer);
}