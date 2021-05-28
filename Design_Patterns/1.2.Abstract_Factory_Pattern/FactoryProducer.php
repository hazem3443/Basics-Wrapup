<?php

namespace Abstract_Factory_Pattern;

include "AbstractFactory.php";

include "ShapeFactory.php";
include "ColorFactory.php";


class FactoryProducer
{
    public function getFactory(string $FactoryName)
    {
        if (strcasecmp($FactoryName, "Color_Factory") == 0) {
            return new ColorFactory();
        } else if (strcasecmp($FactoryName, "Shape_Factory") == 0) {
            return new ShapeFactory();
        }
    }
}
