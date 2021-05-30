# Singleton Pattern

This pattern involves a __single class__ which is responsible to create an object while making sure that only single object gets created. This class provides a way to access its only object which can be accessed directly without need to instantiate the object of the class.

## Implementation

We're going to create a __SingleObject__ class. __SingleObject__ class have its __constructor__ as __private__ and have a static instance of itself.

__SingleObject__ class provides a static method to get its static instance to outside world. __SingletonPatternDemo__, our demo class will use __SingleObject__ class to get a __SingleObject__ object.

![Singleton uml pattern diagram](https://www.tutorialspoint.com//design_pattern/images/singleton_pattern_uml_diagram.jpg)
