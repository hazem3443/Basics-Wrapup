<?php

namespace Bridge_Pattern;

include "DrawAPI.php";

//this class is constructed as a common functionality across childs of it to save construction operation 
//and 
abstract class Shape
{
    protected DrawAPI $drawAPI;

    protected function __construct(DrawAPI $drawAPI)
    {
        $this->drawAPI = $drawAPI;
    }
    abstract function draw();
}

class Circle extends Shape
{
    private int $x, $y, $radius;

    public function __construct(int $x, int $y, int $radius, DrawAPI $drawAPI)
    {
        parent::__construct($drawAPI);
        $this->x = $x;
        $this->y = $y;
        $this->radius = $radius;
    }

    public function draw()
    {
        //this object is declared in parent class (shape) then you can access it directly from this operator 
        $this->drawAPI->drawCircle($this->radius, $this->x, $this->y);
    }
}
