<?php

namespace Abstract_Factory_Pattern;

interface Shape
{
    public function draw();
}

class Circle implements Shape
{
    public function draw()
    {
        echo "Circle::draw()\n";
    }
}
class Rectangle implements Shape
{
    public function draw()
    {
        echo "Rectangle::draw()\n";
    }
}

class Square implements Shape
{
    public function draw()
    {
        echo "Square::draw()\n";
    }
}
class ShapeFactory extends AbstractFactory
{
    //use getShape method to get object of type shape 
    public function getProduct(string $shapeType)
    {
        // echo "\n" . strcasecmp($shapeType, "CIRCLE");
        // echo "\n" . strcasecmp($shapeType, "RECTANGLE");
        // echo "\n" . strcasecmp($shapeType, "SQUARE");

        if ($shapeType == null) {
            return null;
        }
        if (strcasecmp($shapeType, "CIRCLE") == 0) {
            return new Circle();
        } else if (strcasecmp($shapeType, "RECTANGLE") == 0) {
            return new Rectangle();
        } else if (strcasecmp($shapeType, "SQUARE") == 0) {
            return new Square();
        }

        return null;
    }
}
