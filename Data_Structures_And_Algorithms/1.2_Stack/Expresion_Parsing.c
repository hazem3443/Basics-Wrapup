#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

//char type
typedef struct Stack_Type_c
{
    char stack[MAX_SIZE];
    int top;
} StackType_char;

//stack operational functions
int peek_char(StackType_char *stack);
bool isEmpty_char(StackType_char *stack);
bool isFull_char(StackType_char *stack);
int Pop_char(StackType_char *stack);
bool Push_char(StackType_char *stack, int data);
void previewStack_char(StackType_char *stack);

//help functions
int isOperator(char symbol);
int precedence(char symbol);
void reverse(StackType_char *exp);
void brackets(char *exp);

//conversion functions
void convertToPostfix(StackType_char *infix, StackType_char *postfix);
void convertToprefix(StackType_char *infix, StackType_char *postfix);

//evaluation Functions
int evaluatePostfix(StackType_char *postfix);
int evaluatePrefix(StackType_char *prefix);

void main()
{
    StackType_char infix = {"5*(2+4)", 6}; //var is signed char type 127 to -128
    StackType_char postfix = {{0}, -1};
    StackType_char prefix = {{0}, -1};

    convertToPostfix(&infix, &postfix);

    convertToprefix(&infix, &prefix);

    printf("Infix expression is: %s\n\n", infix.stack);

    printf("Postfix expression is: %s\n", postfix.stack);
    printf("Evaluated postfix expression is: %d\n\n", evaluatePostfix(&postfix));

    printf("Prefix expression is: %s\n", prefix.stack);
    printf("Evaluated prefix expression is: %d\n\n", evaluatePrefix(&prefix));
}

void previewStack_char(StackType_char *stack)
{
    printf("+++++STACK+++++\n");
    int x = 0;
    char *s = "PEEK";
    for (x = stack->top; x >= 0; x--, s = "STACK")
    {
        printf("%s -> %d\n", s, stack->stack[x]);
    }
}
int peek_char(StackType_char *stack)
{
    return stack->stack[stack->top];
}
bool isFull_char(StackType_char *stack)
{
    if (stack->top == MAX_SIZE)
        return true;
    else
        return false;
}
bool isEmpty_char(StackType_char *stack)
{
    if (stack->top == -1)
        return true;
    else
        return false;
}
bool Push_char(StackType_char *stack, int data)
{
    if (!isFull_char(stack))
    {
        stack->stack[++stack->top] = data;
        return true;
    }
    else
        return false;
}
int Pop_char(StackType_char *stack)
{
    if (!isEmpty_char(stack))
    {
        return stack->stack[stack->top--];
    }
    else
        return false;
}

//returns precedence of operators
int precedence(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 2;
        break;
    case '*':
    case '/':
        return 3;
        break;
    case '^':
        return 4;
        break;
    case '(':
    case ')':
    case '#':
        return 1;
        break;
    }
}

//check whether the symbol is operator?
int isOperator(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '(':
    case ')':
        return 1;
        break;
    default:
        return 0;
    }
}

//converts infix expression to postfix
void convertToPostfix(StackType_char *infix, StackType_char *postfix)
{
    int i, symbol, j = 0;

    StackType_char stack = {{0}, -1}; //will contain only operators

    Push_char(&stack, '#');
    // stack[++top] = ;

    for (i = 0; i < strlen(infix->stack); i++)
    {
        // printf("postfix = %s\n", postfix->stack);
        // printf("stack = %s\n\n", stack.stack);
        symbol = infix->stack[i];

        if (isOperator(symbol) == 0) //is a number
        {
            Push_char(postfix, symbol);
        }
        else
        {
            if (symbol == '(')
            {
                Push_char(&stack, symbol);
            }
            else
            {
                if (symbol == ')')
                {
                    while (stack.stack[stack.top] != '(')
                    {
                        Push_char(postfix, Pop_char(&stack));
                    }

                    Pop_char(&stack); //pop out (.
                }
                else
                {
                    if (precedence(symbol) > precedence(stack.stack[stack.top]))
                    {
                        Push_char(&stack, symbol);
                    }
                    else
                    {
                        while (precedence(symbol) <= precedence(stack.stack[stack.top]))
                        {
                            Push_char(postfix, Pop_char(&stack));
                        }

                        Push_char(&stack, symbol);
                    }
                }
            }
        }
    }
    // printf("postfix = %s\n", postfix->stack);
    // printf("stack = %s\n\n", stack.stack);

    while (stack.stack[stack.top] != '#')
    {
        Push_char(postfix, Pop_char(&stack));
    }
    Push_char(postfix, '\0');
    // postfix->stack[++postfix->top] = ; //null terminate string.
}

//converts infix expression to prefix
void convertToprefix(StackType_char *infix, StackType_char *prefix)
{
    StackType_char stack = {{0}, -1};
    strcpy(stack.stack, infix->stack);
    stack.top = infix->top;

    reverse(&stack);
    // printf("reversed infix = %s\n", stack.stack);
    brackets(stack.stack);
    // printf("brackets infix = %s\n", stack.stack);

    convertToPostfix(&stack, prefix);

    reverse(prefix);

    // printf("second reverse = %s\n", stack.stack);
    // printf("prefix = %s\n", prefix->stack);

    // printf("inside stack reverse after  = %s top = %i\n", stack.stack, stack.top);
}

void brackets(char *exp)
{
    int i = 0;
    while (exp[i] != '\0')
    {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
        i++;
    }
}

void reverse(StackType_char *exp)
{
    StackType_char stack = {{0}, -1};
    strcpy(stack.stack, exp->stack);
    stack.top = exp->top;
    // printf("inside stack reverse  = %s\n", stack.stack);

    int size = strlen(stack.stack);
    int j = size, i = 0;
    char temp[size];

    temp[j--] = '\0';
    while (stack.stack[i] != '\0')
    {
        temp[j] = stack.stack[i];
        j--;
        i++;
    }
    strcpy(stack.stack, temp);
    // printf("inside stack reverse after  = %s top = %i\n", stack.stack, stack.top);
    // return stack;
    strcpy(exp->stack, stack.stack);
}
//evaluates postfix expression
int evaluatePostfix(StackType_char *postfix)
{
    StackType_char stackint = {{0}, -1};

    char ch;
    int i = 0, operand1, operand2;

    while ((ch = postfix->stack[i++]) != '\0') //starting from stack index 0
    {
        if (isdigit(ch))
        {
            Push_char(&stackint, (ch - '0')); // Push the operand //convert it into a number
        }
        else
        {
            //Operator,pop two operands
            operand2 = Pop_char(&stackint);
            operand1 = Pop_char(&stackint);
            switch (ch)
            {
            case '+':
                Push_char(&stackint, (operand1 + operand2));
                break;
            case '-':
                Push_char(&stackint, operand1 - operand2);
                break;
            case '*':
                Push_char(&stackint, operand1 * operand2);
                break;
            case '/':
                Push_char(&stackint, operand1 / operand2);
                break;
            }
        }
    }

    return stackint.stack[stackint.top];
}

int evaluatePrefix(StackType_char *prefix)
{
    StackType_char stack = {{0}, -1};

    for (int j = prefix->top; j >= 0; j--) //from end to start
    {
        // Push operand to Stack
        // To convert exprsn[j] to digit subtract
        // '0' from exprsn[j].
        if (isdigit(prefix->stack[j]))
            Push_char(&stack, prefix->stack[j] - '0');
        else
        {

            // Operator encountered
            // Pop two elements from Stack
            int o1 = Pop_char(&stack);

            int o2 = Pop_char(&stack);

            // Use switch case to operate on o1
            // and o2 and perform o1 O o2.
            switch (prefix->stack[j])
            {
            case '+':
                Push_char(&stack, o1 + o2);
                break;
            case '-':
                Push_char(&stack, o1 - o2);
                break;
            case '*':
                Push_char(&stack, o1 * o2);
                break;
            case '/':
                Push_char(&stack, o1 / o2);
                break;
            }
        }
    }

    return stack.stack[stack.top];
}