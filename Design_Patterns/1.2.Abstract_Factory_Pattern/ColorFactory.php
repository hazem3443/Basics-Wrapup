<?php

namespace Abstract_Factory_Pattern;

//may be this factory make a different 
interface Color
{
    public function draw();
}

class RED implements Color
{
    public function draw()
    {
        echo "RED::draw()\n";
    }
}
class GREEN implements Color
{
    public function draw()
    {
        echo "GREEN::draw()\n";
    }
}

class BLUE implements Color
{
    public function draw()
    {
        echo "BLUE::draw()\n";
    }
}
class ColorFactory extends AbstractFactory
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
        if (strcasecmp($shapeType, "RED") == 0) {
            return new RED();
        } else if (strcasecmp($shapeType, "GREEN") == 0) {
            return new GREEN();
        } else if (strcasecmp($shapeType, "BLUE") == 0) {
            return new BLUE();
        }

        return null;
    }
}
