#!/usr/bin/php
<?php

namespace Abstract_Factory_Pattern;

include "FactoryProducer.php";
// include "AbstractFactory.php";

//get FactoryProducer 
$FactoryProducer1 = new FactoryProducer();
//get color factory
$colorFactory = $FactoryProducer1->getFactory("Color_Factory");
//get an object of color RED
$color1 = $colorFactory->getProduct("RED");
//call draw method of color RED
$color1->draw();
//get an object of color GREEN 
$color2 = $colorFactory->getProduct("GREEN");
//call draw method of color GREEN
$color2->draw();
//get an object of color BLUE 
$color3 = $colorFactory->getProduct("BLUE");
//call draw method of color BLUE
$color3->draw();

//get shape factory
$shapeFactory = $FactoryProducer1->getFactory("Shape_Factory");
//get an object of Shape Rectangle
$shape1 = $shapeFactory->getProduct("RECTANGLE");
//call draw method of Shape Rectangle
$shape1->draw();
//get an object of Shape Square 
$shape2 = $shapeFactory->getProduct("SQUARE");
//call draw method of Shape Square
$shape2->draw();
//get an object of Shape Circle 
$shape3 = $shapeFactory->getProduct("CIRCLE");
//call draw method of Shape Circle
$shape3->draw();
