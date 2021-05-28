# Abstract Factory Pattern

__Abstract Factory patterns__ work around a super-factory which creates other factories. This factory is also called as __factory of factories__.

In __Abstract Factory pattern__ an interface is responsible for creating a factory of related objects without explicitly specifying their classes. Each generated factory can give the objects as per the __Factory pattern__.

## Implementation

building on __Factory Pattern classes__  
We are going to create a __Color interface__ and a concrete classes(__RED__/__GREEN__/__BLUE__) implementing it. We create an abstract factory class ___AbstractFactory___ as next step. we define Factory class __ColorFactory__, which extends __AbstractFactory__. A factory creator/generator class __FactoryProducer__ is created to handle two factories.

__AbstractFactoryPatternDemo__, our demo class uses __FactoryProducer__ to get an AbstractFactory object. It will pass information (CIRCLE / RECTANGLE / SQUARE for Shape) to AbstractFactory to get the type of object it needs.

![Abstract Factory Pattern UML](https://i.pinimg.com/564x/cc/a7/de/cca7de778f0b68dc25500fc345180383.jpg)
