# Fibonacci Series

Fibonacci series generates the subsequent number by adding two previous numbers.

Fibonacci series satisfies the following conditions −  

- **Fn = Fn-1 + Fn-2**

For illustration purpose, Fibonacci of F8 is displayed as −

![Fibonacci Series](https://www.tutorialspoint.com/data_structures_algorithms/images/fibonacci_animation.gif)

## Fibonacci Iterative Algorithm

First we try to draft the iterative algorithm for Fibonacci series.

```psedo
    Procedure Fibonacci(n)
    declare f0, f1, fib, loop 
    
    set f0 to 0
    set f1 to 1
    
    display f0, f1
    
    for loop ← 1 to n
        fib ← f0 + f1   
        f0 ← f1
        f1 ← fib

        display fib
    end for
    end procedure
```

## Fibonacci Recursive Algorithm

Let us learn how to create a recursive algorithm Fibonacci series. The base criteria of recursion.

```psedo
    START
    Procedure Fibonacci(n)
    declare f0, f1, fib, loop 
    
    set f0 to 0
    set f1 to 1
    
    display f0, f1
    
    for loop ← 1 to n
        fib ← f0 + f1   
        f0 ← f1
        f1 ← fib

        display fib
    end for
    END
```
