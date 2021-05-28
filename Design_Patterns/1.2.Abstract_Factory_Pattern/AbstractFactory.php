<?php

namespace Abstract_Factory_Pattern;

// Abstract classes and methods are when the parent class has a named method, 
// but need its child class(es) to fill out the tasks.

// An abstract class is a class that contains at least one abstract method.
//  An abstract method is a method that is declared, but not implemented in the code.
abstract class AbstractFactory
{
    abstract public function getProduct(string $shapeType);
}
