#!/usr/bin/php
<?php

namespace Facade_Pattern;

include "ShapeMaker.php";

$shapemaker1 = new ShapeMaker();

$shapemaker1->drawCircle();
$shapemaker1->drawRectangle();
$shapemaker1->drawSquare();
