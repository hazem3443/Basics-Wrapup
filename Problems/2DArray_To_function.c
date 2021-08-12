#include <stdio.h>

int print_val(unsigned long int *val);

void main()
{
    unsigned long int arr[100][100] = {{0}};
    arr[10][10] = 100;

    printf("main arr[10][10] %li\n\n", arr[10][10]); //this form is understandable in this scope but into the function it doesn't know about it

    printf("main %p\n", (arr));
    printf("main %p\n", (arr + 10));
    printf("main %li\n\n", *(*(arr + 10) + 10));

    print_val((unsigned long int *)arr);
}

int print_val(unsigned long int *arr)
{
    //retrieve the same in main values from the scope of the function

    printf("in func %p\n", (arr + 0));
    printf("in func %p\n", (arr + (10 * 100)));
    printf("in func %li\n", *((arr + (10 * 100)) + 10)); //here we defined the step of 100 of unsigned long int array size
    // because array is saving row1 col11 col12 col13 row2 col21 col22 col23 row3 col31 col32 col33 and so on
    //and in the scope of a fucntion it doesn't know about array size it just knows that it has a pointer
}