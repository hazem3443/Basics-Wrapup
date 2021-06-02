<?php

namespace Bridge_Pattern;

interface DrawAPI
{
    public function drawCircle(int $radius, int $x, int $y);
}

class RedCircle implements DrawAPI
{
    public function drawCircle(int $radius, int $x, int $y)
    {
        echo ("Drawing Circle[ color: red, radius: " . $radius . ", x: " . $x . ", " . $y . "]\n");
    }
}
class GreenCircle implements DrawAPI
{
    public function drawCircle(int $radius, int $x, int $y)
    {
        echo ("Drawing Circle[ color: green, radius: " . $radius . ", x: " . $x . ", " . $y . "]\n");
    }
}
