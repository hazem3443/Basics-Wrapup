# SOLID

is an acronym for the first five object-oriented design (OOD) principles by Robert C Martin

## SOLID stands for

- S - [Single-responsiblity Principle](#single-responsiblity-principle)
- O - [Open-closed Principle](#open-closed-principle)
- L - [Liskov Substitution Principle](#Liskov-substitution-principle)
- I - [Interface Segregation Principle](#interface-segregation-principle)
- D - [Dependency Inversion Principle](#dependency-inversion-principle)

---

## Single-responsiblity Principle

```markdown
A class should have one and only one reason to change, meaning that a class should have only one job.
```

even it's a job is a method or a property of a defined class

**code example**:

```php
class Square 
{
    public $length;

    public function __construct($length)
    {
        $this->length = $length;
    }
}

class Circle
{
    public $radius;

    public function __construct($radius)
    {
        $this->radius = $radius;
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
            if (is_a($shape, 'Square')) {
                $area[] = pow($shape->length, 2);
            } elseif (is_a($shape, 'Circle')) {
                $area[] = pi() * pow($shape->radius, 2);
            }
        }

        return array_sum($area);
    }

    public function output()
    {
        return implode('', [
          '',
              'Sum of the areas of provided shapes: ',
              $this->sum(),
          '',
      ]);
    }
}

$shapes = [
  new Square(5)
];

$areas = new AreaCalculator($shapes);

echo $areas->output();

```

also to reduce using many classes for our users we can make use of inheritance to make each shape inherite methods from base class such as shapeProperty class such that

```php
class shapeProperties {

    public static function whoAmI() {
        return get_called_class();
    }
    
    public function Area(){
        if (is_a($this, 'Square')) {
            $area = pow($this->length, 2);
            return $area;
            //return "Square";
        } elseif (is_a($this, 'Circle')) {
            $area = pi() * pow($this->radius, 2);
            //return "Circle";
            return $area;
        }
    }
    //...
    //use as many methods as you want the circle and square classes still sees them and can also override them
}
//... Square class extends shape
//... Circle class extends shape
$circle1 = new Circle(5);
echo "\nwho is this area ".$circle1->Area(); //this will give us the previous result
```

also if we want to print output in different formats this will violate this principle so to solve this we create a new class and remove output method inside AreaCalculator class such that

```php
class SumCalculatorOutputter
{
    protected $calculator;

    public function __constructor(AreaCalculator $calculator)
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
              'Sum of the areas of provided shapes: ',
              $this->calculator->sum(),
          '',
      ]);
    }
}
```

and for our second approach we can implement those methods inside shapeProperty class

```php
class shapeProperties {
    ...
    public function JSON()
    {
        ...
    }
    public function HTML()
    {
        ...
    }
}
```
<hr>

## Open-closed Principle
```
Objects or entities should be open for extension but closed for modification.
```
This means that a class should be extendable without modifying the class itself.

Let’s revisit the AreaCalculator class and focus on the sum method which returns the sum of shapes inputed to **AreaCalculator** 

Consider a scenario where the user would like the sum of additional shapes like triangles, pentagons, hexagons, etc. You would have to constantly edit this file and add more if/else blocks. That would violate the open-closed principle.

A way you can make this sum method better is to remove the logic to calculate the area of each shape out of the AreaCalculator class method and attach it to each shape’s class.

Here is the area method defined in Square & Circle:
```php
class Square
{
    public $length;

    public function __construct($length)
    {
        $this->length = $length;
    }

    public function area()
    {
        return pow($this->length, 2);
    }
}
class Circle
{
    public $radius;

    public function construct($radius)
    {
        $this->radius = $radius;
    }

    public function area()
    {
        return pi() * pow($shape->radius, 2);
    }
}
```
also The sum method for AreaCalculator can then be rewritten as:
```php
class AreaCalculator
{
    // ...

    public function sum()
    {
        foreach ($this->shapes as $shape) {
            $area[] = $shape->area();
        }

        return array_sum($area);
    }
}
```
now for each new shape we create we need to define it's area method

**However,** another problem arises. How do you know that the object passed into the AreaCalculator is actually a shape or if the shape has a method named area?

we can solve this by interfaces such that

```php
interface ShapeInterface
{
    public function area();
}
```
and modify your shapes' classes to 
```php
class ... implements ShapeInterface
```
and In the sum method for **AreaCalculator**, you can check if the shapes provided are actually instances of the ShapeInterface; otherwise, throw an exception such that
```php
class AreaCalculator
{
    // ...
    public function sum()
    {
        foreach ($this->shapes as $shape) {
            if (is_a($shape, 'ShapeInterface')) {
                $area[] = $shape->area();
                continue;
            }

            throw new AreaCalculatorInvalidShapeException();
        }
        return array_sum($area);
    }
}
```
 the same idea can be applied with base class that have area method and shapes extends from it so if they are having this class then they have or implements this method but interfaces are more clear and does the job pretty well. 
<hr>

## Liskov Substitution Principle
```
Let q(x) be a property provable about objects of x of type T. Then q(y) should be provable for objects y of type S where S is a subtype of T.
```
this pattern states that if an object B inherits from object A then all properties of type A is provable for objects of type B or can be handled without any problem

for substituting 
talk(animal_obj) - animal_obj is an object of type animal and talk is a method can be applied to that object
talk(bird_obj)   - bird_obj is an object of type bird and talk method can be applied to it where bird is a subtype of (inherits from) animal type

it seems obvious that we didn't need to explain that but **This means that every subclass(child) or derived class should be substitutable(replacable) for their base or parent class.**which means child class have the parent method and properties

Building off the example **AreaCalculator** class, consider a new **VolumeCalculator** class that extends the **AreaCalculator** class:
```php
class VolumeCalculator extends AreaCalculator
{
    public function construct($shapes = [])
    {
        parent::construct($shapes);
    }

    public function sum()
    {
        // logic to calculate the volumes and then return an array of output
        return [$summedData];
    }
}
```
**remember** the method of **SumCalculatorOutputter** which can be applied to both area and volume classes which has **sum** method (can be inserted or implements this as interface) and each class implements it should has it 

so for conclusion on our example 
```
VolumeCalculator is subcalss of AreaCalculator then property SumCalculatorOutputter should be fine for both of them as they both have the same method **sum** but VolumeCalculator overrides it with it's implementation 
```
<hr>

## Interface Segregation Principle
```
A client should never be forced to implement an interface that it doesn’t use, or clients shouldn’t be forced to depend on methods they do not use.
```
this mean you need to separate interfaces and only implement the one you need or will depend on later.

```php
interface ShapeInterface
{
    public function area();
}

interface ThreeDimensionalShapeInterface
{
    public function volume();
}
class Cuboid implements ShapeInterface, ThreeDimensionalShapeInterface
{....
```
and only implements the one you need or depend on.
also, for type-hinting or use your interface method inside another interface method you can do it such that
```php
interface ManageShapeInterface
{
    public function calculate();
}
class Square implements ShapeInterface, ManageShapeInterface
{...
public function calculate()
    {
        //do logic
        return $this->area();
    }

}
class Cuboid implements ShapeInterface, ThreeDimensionalShapeInterface, ManageShapeInterface
{...
public function calculate()
    {
        //do different login but both are depend on area method inside ShapeInterface
        return $this->area();
    }
}

```
<!-- <span style="background-color: #FF0000">highlighted text</span> -->
Now in **AreaCalculator** class, you can replace the call to the area method with calculate and also check if the object is an instance of the **ManageShapeInterface** and not the **ShapeInterface**.

`that mean you can nest methods from different interfaces inside each other but you should create different interface for each new method and make sure you implement both the base interface and the derived interface`

That satisfies the interface segregation principle.
<hr>

## Dependency Inversion Principle
```
Entities must depend on abstractions, not on concretions. It states that the high-level module must not depend on the low-level module, but they should depend on abstractions.
```
This principle allows for decoupling and make layers independent.

Here is an example of a PasswordReminder that connects to a MySQL database:
```php
class MySQLConnection
{
    public function connect()
    {
        // handle the database connection
        return 'Database connection';
    }
}

class PasswordReminder
{
    private $dbConnection;

    public function __construct(MySQLConnection $dbConnection)
    {
        $this->dbConnection = $dbConnection;
    }
}
```
First, the **MySQLConnection** is the low-level module while the **PasswordReminder** is high level,
**PasswordReminder** class is being forced to depend on the **MySQLConnection** class this would violate the **Dependency Inversion Principle**.

`Later`, if you were to change the database engine, you would also have to edit the **PasswordReminder** class, and this would violate the open-close principle.

The **PasswordReminder** class should not care what database your application uses. To address these issues, you can code to an interface since high-level and low-level modules should depend on abstraction:

```php
interface DBConnectionInterface
{
    public function connect();
}
```
The interface has a connect method and the **MySQLConnection** class implements this interface. Also, instead of directly type-hinting **MySQLConnection** class in the constructor of the **PasswordReminder**, you instead type-hint the **DBConnectionInterface** and no matter the type of database your application uses, the **PasswordReminder** class can connect to the database without any problems and open-close principle is not violated.

```php
class MySQLConnection implements DBConnectionInterface
{
    public function connect()
    {
        // handle the database connection
        return 'Database connection';
    }
}

class PasswordReminder
{
    private $dbConnection;

    public function __construct(DBConnectionInterface $dbConnection)
    {
        $this->dbConnection = $dbConnection;
    }
}
```

This code establishes that both the high-level and low-level modules depend on abstraction.