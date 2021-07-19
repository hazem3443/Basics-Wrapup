#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
  Higher order functions are functions that operate on other
  functions, either by taking them as arguments or by returning
  them.
  
  In simple words, A Higher-Order function is a function that
  receives a function as an argument or returns the function as
  output.
*/

void *Higher_Order_Function(void (*fun_a)(int)); //function takes a function
void inner_function(int i);

typedef struct
{
    int array[100];
    int length;
} array_type;

void ForEach(array_type *arr1, bool (*fun_a)(int));
bool func_for_element_foreach(int i);

void Map(array_type *arr1, array_type *result, bool (*fun_a)(int));
bool func_for_element_forMap(int i);

void Filter(array_type *arr1, array_type *result, bool (*fun_a)(int));
bool func_for_element_forFilter(int i);

int Reduce(array_type *arr1, array_type *result, int (*fun_a)(int *, int));
int func_for_element_forReduce(int *acc, int i);

void main()
{
    void (*fun_b)(int) = Higher_Order_Function(inner_function);
    fun_b(10);

    array_type arr1 = {{1, 2, 3, 4, 5}, 5};
    array_type result = {{0, 0, 0, 0, 0}, 5}; //return of each function

    printf("----------ForEach function----------\n");
    ForEach(&arr1, func_for_element_foreach);
    printf("----------Map function----------\n");
    Map(&arr1, &result, func_for_element_forMap);

    printf("\t Results\n");
    for (int i = 0; i < result.length; i++)
        printf("arr[%i] = %i\t", i, result.array[i]);
    printf("\n\n");

    printf("----------Filter function----------\n");
    Filter(&arr1, &result, func_for_element_forFilter);

    printf("\t Results\n");
    for (int i = 0; i < result.length; i++)
        printf("arr[%i] = %i\t", i, result.array[i]);
    printf("\n\n");

    printf("----------Reduce function----------\n");
    printf("\t Reduce Results = %i \n", Reduce(&arr1, &result, func_for_element_forReduce));
}

void *Higher_Order_Function(void (*fun_a)(int))
{
    fun_a(1);
    printf("Inside Higher Order Function 1\n");
    return inner_function;
}

void inner_function(int i)
{
    printf("Inside Inner Function %i\n", i);
}

void ForEach(array_type *arr1, bool (*fun_a)(int))
{
    for (int i = 0; i < arr1->length; i++)
        fun_a(arr1->array[i]);
}
bool func_for_element_foreach(int i)
{
    printf("Inside func_for_element  i = %i\n", i);
}

void Map(array_type *arr1, array_type *result, bool (*fun_a)(int))
{
    for (int i = 0; i < arr1->length; i++)
        result->array[i] = fun_a(arr1->array[i]);
    result->length = arr1->length;
}
bool func_for_element_forMap(int i)
{
    printf("Inside func_for_element  i = %i\n", i);
    return i > 2;
}

void Filter(array_type *arr1, array_type *result, bool (*fun_a)(int))
{
    for (int i = 0; i < arr1->length; i++)
        result->array[i] = ((fun_a(arr1->array[i])) == true) ? i : 0;

    result->length = arr1->length;
}
bool func_for_element_forFilter(int i)
{
    printf("Inside func_for_element  i = %i\n", i);
    return i > 2;
}

int Reduce(array_type *arr1, array_type *result, int (*fun_a)(int *, int))
{
    int acc = arr1->array[0];
    // int prev_acc = 0;
    for (int i = 1; i < arr1->length; i++)
    {
        // prev_acc = acc;
        acc = fun_a(&acc, arr1->array[i]);
    }
    result->length = arr1->length;
    return acc;
}
int func_for_element_forReduce(int *acc, int i)
{
    *acc += i;
    // printf("Inside func_for_element  i = %i acc = %i \n", i, *acc);

    return *acc;
}