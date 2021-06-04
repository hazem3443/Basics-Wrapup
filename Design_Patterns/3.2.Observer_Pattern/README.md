# Observer Pattern

Observer pattern is used when there is one-to-many relationship between objects such as if one object is modified, its depenedent objects are to be notified automatically.

## Implementation

Observer pattern uses __three actor classes__. __Subject__, __Observer__ and __Client__. __Subject__ is an object having methods to attach and detach __observers__ to a __client__ object. We have created an abstract class __Observer__ and a concrete class __Subject__ that is extending class __Observer__.

__ObserverPatternDemo__, our demo class, will use Subject and concrete class object to show observer pattern in action.

![Observer Pattern UML diagram](https://www.tutorialspoint.com/design_pattern/images/observer_pattern_uml_diagram.jpg)
