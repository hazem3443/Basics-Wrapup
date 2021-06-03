<?php

namespace Strategy_Pattern;

interface Strategy
{
    public function doOperation(int $num1, int $num2): int;
}

class OperationAdd implements Strategy
{
    public function doOperation(int $num1, int $num2): int
    {
        return $num1 + $num2;
    }
}

class OperationSubstract implements Strategy
{
    public function doOperation(int $num1, int $num2): int
    {
        return $num1 - $num2;
    }
}

class OperationMultiply implements Strategy
{
    public function doOperation(int $num1, int $num2): int
    {
        return $num1 * $num2;
    }
}
