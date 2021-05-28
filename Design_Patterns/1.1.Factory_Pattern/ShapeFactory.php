<?php

namespace Factory_Pattern;

// include "Circle.php";
// new Circle();
class ShapeFactory
{
    //use getShape method to get object of type shape 
    public function getShape(string $shapeType)
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
