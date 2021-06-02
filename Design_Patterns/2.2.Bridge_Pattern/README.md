# Bridge Pattern

Bridge is used when we need to __decouple an abstraction from its implementation__ so that the two can vary independently.
this pattern decouples implementation class and abstract class by providing a bridge structure between them.

This pattern involves an __interface__ which acts as a bridge which makes the functionality of concrete classes independent from interface implementer classes. Both types of classes can be altered structurally without affecting each other.

## Implementation

We have a __DrawAPI__ interface which is acting as a bridge implementer and concrete classes __RedCircle__, __GreenCircle__ implementing the __DrawAPI__ interface. __Shape__ is an abstract class and will use object of __DrawAPI__.
__BridgePatternDemo__, our demo class will use Shape class to draw different colored circle.

![bridge pattern UML diagram](https://www.tutorialspoint.com/design_pattern/images/bridge_pattern_uml_diagram.jpg)
