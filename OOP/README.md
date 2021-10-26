  
# OOP Basics

JavaScript is not a class-based object-oriented language But it still has ways of using OOP so for now we will use C++

## 1. classes Vs Objects

- a class is a template ( or type) for objects, and an object is an instance of a class
- for example Car is a class and audi,volvo and BMW is an object of car class
- **Create a Class**
  
  ```cpp
  class MyClass {       // The class
  public:             // Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
  };
  ```

- **Create Object**

  ```cpp
  MyClass myObj1;
  MyClass myObj2;
  ```

## 2. Class Methods

- There are two ways to define functions that belongs to a class:
  - Inside class definition
  - Outside class definition
- Inside Example
  
  ```cpp
  class MyClass {        // The class
    public:              // Access specifier
      void myMethod() {  // Method/function defined   inside the class
        cout << "Hello World!";
      }
  };
  ```

- Outside Example
  
  ```cpp
  class MyClass {        // The class
  public:              // Access specifier
      void myMethod();   // Method/function declaration
  };

    // Method/function definition outside the class
    void MyClass::myMethod() {
        cout << "Hello World!";
    }
  ```

## 3. Constructors & Destructors

- A constructor in C++ is a special method that is automatically called when an object of a class is created
- Destructors is a special method that is automatically called when an object of a class is removed from memory or deleted from malloced memory which should be called within new or our script is going to delete it.
- Example

  ```cpp
    class MyClass {     // The class
        public:           // Access specifier
            //constructor
            MyClass() {     // Constructor
                cout << "object created!";
            }
            //destructor
            ~MyClass() {     // Constructor
                cout << "object destroyed!";
            }
    };
  ```

- **Note**: The constructor has the same name as the class, it is always public, and it does not have any return value.
- constructors can also be defined outside the class, Just like functions (interfaces).

## 4. Access Specifiers

- The public keyword is an access specifier. Access specifiers define how the members (attributes and methods) of a class can be accessed.
- there are three access specifiers:

  - `public`- members are accessible from outside the class
  - `private` - members cannot be accessed (or viewed) from outside the class
  - `protected` - members cannot be accessed from outside the class, however, they can be accessed in inherited classes.

- **Note**: It is possible to access private members of a class using a public method inside the same class.
- **Tip**: It is considered good practice to declare your class attributes as private (as often as you can). This will reduce the possibility of yourself (or others) to mess up the code

## 5. Encapsulation

- Encapsulation, is to make sure that "sensitive" data is hidden from users. To achieve this, you must declare class variables/attributes as private. If you want others to read or modify the value of a private member, you can provide public get and set methods.
-**Access Private Members**
  
  ```cpp
  class Employee {
    private:
      // Private attribute
      int salary;

    public:
      // Setter
      void setSalary(int s) {
        salary = s;
      }
      // Getter
      int getSalary() {
        return salary;
      }
  };
  ```

- **Why Encapsulation?**
  - It is considered good practice to declare your class attributes as private (as often as you can). Encapsulation ensures better control of your data, because you (or others) can change one part of the code without affecting other parts
  - Increased security of data

## 6. Inheritance

- **inheritance concept** have two categories:
  - derived class (child) - the class that inherits from another class
  - base class (parent) - the class being inherited from
  
  ```cpp
  // Base class
  class Vehicle {
    public:
      string brand = "Ford";
      void honk() {
        cout << "Tuut, tuut! \n" ;
      }
  };
    
  // Derived class
  class Car: public Vehicle {
    public:
      string model = "Mustang";
  };
  ```

- **Why And When To Use "Inheritance"?**
  - It is useful for code reusability: reuse attributes and methods of an existing class when you create a new class.

- ### 1. **Multilevel Inheritance**

  - A class can also be derived from one class, which is already derived from another class.
  
  ```cpp
  // Base class (parent)
  class MyClass {
    public:
      void myFunction() {
        cout << "Some content in parent class." ;
      }
  };

  // Derived class (child)
  class MyChild: public MyClass {
  };

  // Derived class (grandchild)
  class MyGrandChild: public MyChild {
  };
  ```

- ### 2. **Multiple Inheritance**

  - A class can also be derived from more than one base class, using a comma-separated list:
  
  ```cpp
  // Base class
  class MyClass {
    public:
      void myFunction() {
        cout << "Some content in parent class." ;
      }
  };

  // Another base class
  class MyOtherClass {
    public:
      void myOtherFunction() {
        cout << "Some content in another class." ;
      }
  };

  // Derived class
  class MyChildClass: public MyClass, public MyOtherClass {
  };
  ```

## 7. Polymorphism

- **Polymorphism** means "many forms", and it occurs when we have many classes that are related to each other by inheritance.
- allows us to perform a single action in different ways.
  - **For example**, think of a base class called Animal that has a method called animalSound(). Derived classes of Animals could be Pigs, Cats, Dogs, Birds - And they also have their own implementation of an animal sound (the pig oinks, and the cat meows, etc.):
  
  ```cpp
  // Base class
  class Animal {
    public:
      void animalSound() {
      cout << "The animal makes a sound \n" ;
    }
  };
    
  // Derived class
  class Pig : public Animal {
    public:
      void animalSound() {
      cout << "The pig says: wee wee \n" ;
    }
  };
    
  // Derived class
  class Dog : public Animal {
    public:
      void animalSound() {
      cout << "The dog says: bow wow \n" ;
    }
  };
  ```

- **Why And When To Use "Inheritance" and "Polymorphism"?**
  - It is useful for code reusability: reuse attributes and methods of an existing class when you create a new class.
- **METHOD OVERRIDING** : It is when a subclass implements its own version of a method that was inherited from its parent class. This type of polymorphism is also called “method overriding”, or “runtime polymorphism”.

- **METHOD OVERLOADING** : This is when two methods have the same name, but different parameters. Method overloading can happen in two ways. This is also called “compile-time polymorphism”.
  - First, the number of parameters changes. For example, the overriding method adds new parameters or removes exist.
  - Second, the type of parameters changes. The inherited method takes a parameter of type number as a parameter. Then, you create overriding method that takes a parameter of type string as a parameter instead.
  - **note** that method or function overloading is scope specific so we can't perform it on two different classes because it is in different scopes but in the same scope we can achieve that property which happens in compile time
  - **also Note** that virtual function make sure that your polymorphic function binds in run-time if you call a method by it's reference you can notice that compiler binds method to classes in compile time so calling methods by its refernce keeps the base class method refernce with no change but to achieve runtime polymorphism

## 8. Abstraction

- Abstraction means displaying only essential information and hiding the details.
- Data abstraction refers to providing only essential information about the data to the outside world, hiding the background details or implementation.
- Consider a real life example of a man driving a car. The man only knows that pressing the accelerators will increase the speed of car or applying brakes will stop the car but he does not know about how on pressing accelerator the speed is actually increasing, he does not know about the inner mechanism of the car or the implementation of accelerator, brakes etc in the car.
