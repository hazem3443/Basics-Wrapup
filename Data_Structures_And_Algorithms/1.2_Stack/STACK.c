#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct Stack_Type
{
    int stack[MAX_SIZE];
    int top;
} StackType;

int peek(StackType *stack);
bool isEmpty(StackType *stack);
bool isFull(StackType *stack);

int Pop(StackType *stack);
bool Push(StackType *stack, int data);

void previewStack(StackType *stack);

StackType stack1 = {{0}, -1};

void main()
{
    Push(&stack1, 10);
    Push(&stack1, 11);
    Push(&stack1, 12);
    Push(&stack1, 13);
    Push(&stack1, 14);
    Push(&stack1, 15);
    Push(&stack1, 16);
    Push(&stack1, 17);
    Push(&stack1, 18);
    Push(&stack1, 19);
    Push(&stack1, 20);

    previewStack(&stack1);

    Pop(&stack1);
    Pop(&stack1);

    previewStack(&stack1);

    printf("STACK Peek = %d\n", peek(&stack1));
}

void previewStack(StackType *stack)
{
    printf("+++++STACK+++++\n");
    int x = 0;
    char *s = "PEEK";
    for (x = stack->top; x >= 0; x--, s = "STACK")
    {
        printf("%s -> %d\n", s, stack->stack[x]);
    }
}
int peek(StackType *stack)
{
    return stack->stack[stack->top];
}
bool isFull(StackType *stack)
{
    if (stack->top == MAX_SIZE - 1)
        return true;
    else
        return false;
}
bool isEmpty(StackType *stack)
{
    if (stack->top == -1)
        return true;
    else
        return false;
}
bool Push(StackType *stack, int data)
{
    if (!isFull(stack))
    {
        stack->stack[++stack->top] = data;
        return true;
    }
    else
        return false;
}

int Pop(StackType *stack)
{
    if (!isEmpty(stack))
    {
        return stack->stack[stack->top--];
    }
    else
        return false;
}