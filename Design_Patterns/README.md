# Design Patterns

In **1994**, four authors Erich Gamma, Richard Helm, Ralph Johnson and John Vlissides published a book titled Design Patterns - Elements of Reusable Object-Oriented Software which initiated the concept of Design Pattern in Software development.

- ## Types of Design Patterns
  
  - [Creational Patterns](#creational-patterns)
    - [Factory Pattern](1.1.Factory_Pattern)
    - [Abstract Factory Pattern](1.2.Abstract_Factory_Pattern)
    - [Singleton Pattern](1.3.Singleton_Pattern)
  - [Structural Patterns](#structural-patterns)
    - [Facade Pattern](2.1.Facade_Pattern)
    - [Bridge/Adapter Pattern](2.2.Bridge/Adapter_Pattern)
  - [Behavioral Patterns](#behavioral-patterns)
    - [Strategy Pattern](3.1.Strategy_Pattern)
    - [Observer Pattern](3.2.Observer_Pattern)

### Creational Patterns

```markdown
 These design patterns provide a way to create objects while hiding the creation logic,
 rather than instantiating objects directly using new operator. 
 This gives program more flexibility in deciding 
 which objects need to be created for a given use case.
```

### Structural Patterns

```markdown
These design patterns concern class and object composition.
Concept of inheritance is used to compose interfaces
and define ways to compose objects to obtain new 
functionalities.
```

### Behavioral Patterns

```markdown
These design patterns are specifically concerned with communication between objects.
```

## Notice

 ___to run php in command line ubuntu you can follow these steps___

- setup php for ubuntu  

```bash
   sudo apt install php7.3-cli php7.3-fpm php7.3-json php7.3-pdo php7.3-mysql php7.3-zip php7.3-gd  php7.3-mbstring php7.3-curl php7.3-xml php7.3-bcmath php7.3-json
```

- add this **shebang** to your first line of code

```php
  #!/usr/bin/php
```

- make the *.php file executable
  
  ```bash
  chmod 755 *.php
  ```

- run code in terminal such that
  
  ```bash
  ./*.php
  ```
