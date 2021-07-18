#include <stdio.h>

#define MAX_SIZE 100

typedef struct
{
    int stack[MAX_SIZE];
    int top;
} Stack_type;

Stack_type Source = {{0}, -1};
Stack_type Destination = {{0}, -1};
Stack_type Auxilarity = {{0}, -1};

void printStack(Stack_type *stack);
int Pop(Stack_type *stack);
void Push(Stack_type *stack, int val);

void initializeHanoi_Tower(Stack_type *stack, int tower_height);
void Hanoi_procedure(int src_stack_top, Stack_type *src, Stack_type *dest, Stack_type *aux);

void main()
{
    int tower_height = 3;
    initializeHanoi_Tower(&Source, tower_height);
    // printStack(&Source);
    // printf("point");
    Hanoi_procedure(tower_height, &Source, &Destination, &Auxilarity);
    printf("\n");
    printStack(&Source);
    printStack(&Destination);
    printStack(&Auxilarity);
    printf("\n");
}

void printStack(Stack_type *stack)
{
    int stack_len = &stack->stack[stack->top] - stack->stack;
    printf("%s [%i] = [ ", ((stack == &Source) ? "Source " : (stack == &Destination) ? "Destination"
                                                                                     : "Auxilary"),
           stack_len + 1);
    for (int i = 0; printf(" ") && i <= stack_len; i++)
        printf("%i,", stack->stack[i]);
    printf("\b\b ] ");
}

void Push(Stack_type *stack, int val)
{
    stack->stack[++stack->top] = val;
}
int Pop(Stack_type *stack)
{
    return stack->stack[stack->top--];
}
void initializeHanoi_Tower(Stack_type *stack, int tower_height)
{
    for (int i = tower_height; i > 0; i--)
        Push(stack, i);
}

void Hanoi_procedure(int src_stack_top, Stack_type *src, Stack_type *dest, Stack_type *aux)
{
    if (src_stack_top == 1)
    {
        printf("Move disk 1 from rod \t'%s'\t to rod  \t'%s'\t\t-----\t\t", ((src == &Source) ? "Source " : (src == &Destination) ? "Destination"
                                                                                                                                  : "Auxilary"),
               ((dest == &Source) ? "Source " : (dest == &Destination) ? "Destination"
                                                                       : "Auxilary"));
        printf(" before n = %i ", src_stack_top);
        printStack(src);
        printStack(dest);
        printStack(aux);
        printf("\n");

        Push(dest, Pop(src)); //move disk from source to destination
    }
    else
    {
        Hanoi_procedure(src_stack_top - 1, src, aux, dest);
        printf("Move disk %i from rod \t'%s'\t to rod  \t'%s'\t\t-----\t\t", src_stack_top, ((src == &Source) ? "Source " : (src == &Destination) ? "Destination"
                                                                                                                                                  : "Auxilary"),
               ((dest == &Source) ? "Source " : (dest == &Destination) ? "Destination"
                                                                       : "Auxilary"));
        printf(" before n = %i ", src_stack_top);
        printStack(src);
        printStack(dest);
        printStack(aux);
        printf("\n");

        Push(dest, Pop(src)); //move disk from soirce to destination
        Hanoi_procedure(src_stack_top - 1, aux, dest, src);
    }
}