<?php

namespace Facade_Pattern;

include "Shape.php";

class ShapeMaker
{
    private $circle;
    private $rectangle;
    private $square;

    function __construct()
    {
        $this->circle = new Circle();
        $this->rectangle = new Rectangle();
        $this->square = new Square();
    }

    public function drawCircle()
    {
        $this->circle->draw();
    }
    public function drawRectangle()
    {
        $this->rectangle->draw();
    }
    public function drawSquare()
    {
        $this->square->draw();
    }
}
