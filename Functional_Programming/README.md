# Functional Programming in C Language

## Functions Assigned to Variables

this is happened by defining a function pointer and assign this pointer to another pointer such that

```c
    void (*func)(int); //this is a function pointer definition with name func
    //suppose we have a function that prints its input named printInput
    //we can assign this function pointer to printInput function such that we
    func = printInput;
    //so now when we can call func and use it as we use printInput function
```

## Callback Functions

a callback function is a function that is passed into another function as an argument.
such as NVIC callbacks or interrupts of the cpu that is defined within startup code to define callbacks of each interupt event and its' function call that is a user side code,defined earlier in the code but need to be linked within interrupt vector table

or the callback functions can be used in layered architecture to isolate low level events such as (interrupts or urgent memory calls) from high level code (user code)

## Higher Order Function

A **higher-order function** is a function that accepts functions as parameters and/or returns a function.
such as **Higher_Order_Function** in the linked script.

## **ForEach** Function

this function executes a callback function on each of the elements in an array in order.

## **Map** Function

this function executes a callback function on each element in an array and produces a new array made up of the return values from the callback function in **result** passed array.

The original array does not get altered, and the returned array may contain different elements than the original array.

## **Filter** Function

this function executes a callback function on each element in an array. The callback function for each of the elements must return either **true** or **false**. The generated array is a new array with any indecies for which the callback function returns **true**.

## **Reduce** Function

this function executes a callback function with two parameters (**accumulator, currentValue**) as arguments. On each iteration, accumulator is the value returned by the last iteration, and the currentValue is the current element. Optionally, a second argument can be passed which acts as the initial value of the accumulator.
