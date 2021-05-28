# Factory Pattern

__In Factory pattern,__ we create object without exposing the creation logic to the client and refer to newly created object using a common interface.

this pattern provides one of the best ways to create an object.

## Implementation

We're going to create a __Shape__ interface and concrete classes (__CIRCLE__ / __RECTANGLE__ / __SQUARE__) implementing the Shape interface. A factory class __ShapeFactory__ is defined as a next step.

__FactoryPatternDemo__, our demo class will use ShapeFactory to get a Shape object. It will pass information (CIRCLE / RECTANGLE / SQUARE) to ShapeFactory to get the type of object it needs.

![Factory Pattern UML Diagram](https://www.tutorialspoint.com/design_pattern/images/factory_pattern_uml_diagram.jpg)
