<?php

namespace Facade_Pattern;

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
