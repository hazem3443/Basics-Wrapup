# Facade Pattern

this pattern adds an interface to existing system to hide its complexities.

This pattern involves a single class which provides simplified methods required by client and delegates calls to methods of existing system classes.

## Implementation

We are going to create a __Shape__ interface and concrete classes implementing the __Shape__ interface as bfore . A facade class __ShapeMaker__ is defined as a next step.

__ShapeMaker__ class uses the concrete classes to delegate user calls to these classes. __FacadePatternDemo__, our demo class, will use ShapeMaker class to show the results.

![Facade Pattern UML diagram](https://www.tutorialspoint.com/design_pattern/images/facade_pattern_uml_diagram.jpg)
