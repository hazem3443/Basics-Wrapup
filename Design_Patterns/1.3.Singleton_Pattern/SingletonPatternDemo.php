#!/usr/bin/php
<?php

namespace SingletonPattern;

include "SingleObject.php";
//illegal construct
//Compile Time Error: The constructor SingleObject() is not visible
// $object = new SingleObject();
//it is private static so you can't access it from outside it will log an compile time error 

//Get the only object available
//this method is independent from whole class body except $instance object which is dependent to class scope but not accessible 
//each call to this method returns the same object which created before so you can't create more than one object

$object = SingleObject::getInstance();

//show the message
$object->showMessage();

// echo $object->getname();
// $object->setname("hazem");
// echo $object->getname();
