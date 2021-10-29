<?php

interface ShapeInterface
{
    public function Area();
    public function dimension();
}
interface ThreeDimensionalShapeInterface
{
    public function volume();
}
/*
class shapeProperties {

    public static function whoAmI() {
        return get_called_class();
    }
    
    public function Area(){} //each child should implement it independently
    public function Length(){
        return $this->dimension();//this refer to the inherited class scope(shapes' class scope)
    }
    
    public function JSON()
    {
        $data = [
          'sum' => $this->Area(),
      ];

        return json_encode($data);
    }

    public function HTML()
    {
        return implode('', [
          '',
              'Sum of the areas of provided shapes: ',
              $this->Area(),
          '',
      ]);
    }
}
*/

class Square implements ShapeInterface
{
    public $length;

    public function __construct($length)
    {
        $this->length = $length;
    }
    public function Area()
    {
        return pow($this->length, 2);
    }
    public function Volume()
    {
        return $this->Area() * 6;
    }
    public function dimension()
    {
        return $this->length;
    }
}

class Cuboid extends Square implements ThreeDimensionalShapeInterface
{
    public function __construct($length)
    {
        parent::__construct($length);
    }
    public function Area()
    {
        return parent::Area() * 6;
        // calculate the surface area of the cuboid
    }

    public function Volume()
    {
        // calculate the volume of the cuboid
        return pow($this->dimension(), 3);
    }
    public function dimension()
    {
        return parent::dimension();
    }
}

class Circle implements ShapeInterface
{
    public $radius;

    public function __construct($radius)
    {
        $this->radius = $radius;
    }
    public function Area()
    {
        return pi() * pow($this->radius, 2);
    }
    public function Volume()
    {
        return $this->Area() * (4 / 3) * $this->radius;
    }
    public function dimension()
    {
        return $this->radius;
    }
}

class Spheroid extends Circle implements ThreeDimensionalShapeInterface
{
    public function __construct($radius)
    {
        parent::__construct($radius);
    }
    public function Area()
    {
        return parent::Area() * 4;
        // calculate the surface area of the cuboid
    }

    public function Volume()
    {
        // calculate the volume of the cuboid
        return 4 / 3 * pi() * pow($this->dimension(), 3);
    }
    public function dimension()
    {
        return parent::dimension();
    }
}
class AreaCalculator
{
    protected $shapes;

    public function __construct($shapes = [])
    {
        $this->shapes = $shapes;
    }

    public function sum()
    {
        foreach ($this->shapes as $shape) {
            if (is_a($shape, 'ShapeInterface')) {
                $area[] = $shape->Area();
                continue;
            }
            throw new AreaCalculatorInvalidShapeException();
        }

        return array_sum($area);
    }
}
//this scope is for explaining interface way to satisfy open-close principal
/*
interface solidShapeProperties
{
    public function volume();
}
class solidShape implements solidShapeProperties{
    //..constructor with dimension and position
    //..volume method claculator
}
//end dummy scope above
*/
//but we can use the previous shape classes to find it's volume from it's dimensions
class VolumeCalculator extends AreaCalculator
{
    public function __construct($shapes = [])
    {
        parent::__construct($shapes);
    }

    public function sum()
    {
        // logic to calculate the volumes and then return an array of output
        foreach ($this->shapes as $shape) {
            if (is_a($shape, 'ShapeInterface')) {
                $summedvolume[] = $shape->Volume();
                continue;
            }
            throw new VolumeCalculatorInvalidShapeException();
        }

        return array_sum($summedvolume);
    }
}
//not changes for liskov principal
class SumCalculatorOutputter
{
    protected $calculator;

    public function __construct(AreaCalculator $calculator)
    {
        $this->calculator = $calculator;
    }

    public function JSON()
    {
        $data = [
            'sum' => $this->calculator->sum(),
        ];

        return json_encode($data);
    }

    public function HTML()
    {
        return implode('', [
            '',
            "Sum of the areas of provided shapes: ",
            $this->calculator->sum(),
            '',
        ]);
    }
}
$shapes = [
    new Square(5),
    new Circle(4.5)
];

// $areas = new AreaCalculator($shapes);
// $volumes= new VolumeCalculator($shapes);

// $out1 = new SumCalculatorOutputter($areas);
// echo "\n".$out1->HTML();
// echo "\n".$out1->JSON();

// $out2 = new SumCalculatorOutputter($volumes);
// echo "\n".$out2->HTML();
// echo "\n".$out2->JSON();

// echo "\n".$areas->sum();
// echo "\n".$volumes->sum();

// echo "\n".$shapes[0]->dimension();
// echo "\n".$shapes[0]->Volume();

// echo "\n".$shapes[1]->dimension();
// echo "\n".$shapes[1]->Volume();

// $i = new Square(5);
// echo "\nthis area ".$i->Area();
// echo $i->Length();

// $i = new Circle(2);
// echo "\nthis area ".$i->Area();
// echo $i->Length();

// echo "\nthis area :\n".$i->JSON();
// echo "\nthis area :\n".$i->HTML();

$cube1 = new Cuboid(5);
echo "\ncube l = " . $cube1->dimension();
echo "\ncube surface Area = " . $cube1->Area();
echo "\ncube Volume l = " . $cube1->Volume();

$sphere1 = new Spheroid(5);
echo "\nsphere l = " . $sphere1->dimension();
echo "\nsphere surface Area = " . $sphere1->Area();
echo "\nsphere Volume l = " . $sphere1->Volume();

$SolidShapes = [$cube1, $sphere1];
$areas = new AreaCalculator($SolidShapes);
$volumes = new VolumeCalculator($SolidShapes);
echo "\n" . $areas->sum();
echo "\n" . $volumes->sum();

$out1 = new SumCalculatorOutputter($areas);
echo "\n" . $out1->HTML();
echo "\n" . $out1->JSON();

$out2 = new SumCalculatorOutputter($volumes);
echo "\n" . $out2->HTML();
echo "\n" . $out2->JSON();
