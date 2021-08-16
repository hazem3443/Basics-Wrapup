# Introduction To Autosar

## why Autosar?

1. used by automotive companies as a standard architecture and deployed on most cars

2. startedin 2003 as a mature Software from previous experiences of car manufacturers

3. excellent way to understand SW Design

4. can use the same concepts in other fields

5. a must known skill for any embedded SW engineer

## the 4 Reasons for Existence

- **Modularity**
ability to customize the SW based on the **ECU** functionality

- **Scalability**
Avoid SW redundancy by using the same standard modules on all **ECUs**

- **Transferability**
ability to transfer a SW application from **ECU** to another to optimize the use of available resources

- **Interoperability**
by standardinzing interfaces between different SW layers which enables using SW and HW from different suppliers
or it is the ability of a component to work with other components without any problem

## a glimpse of history

Autosar slogans

- cooperate on standardd , compete on implementation
- Enable continuous innovation

## Autosar Config & integration Roles

- Role : based on project and you may have many roles
- title: such as **Automotive Software Engineer** or **Senior Software Engineer** and you only have one title

1. Basic Pre-Configuration & Integration Role  
this stage makes sure that each module is working in a very basic senario without applying customer app just to test module is working but not testing it's integrability or deep bugs found on level of integration

2. Basic SW configuration & integration Role  
in this role you exposed to :  

    **SWS** (Software Specifications) : talks about apis in software detailes specs and its params we need to look at it to understand how to implement a certain stack

    **SRS** (Software Requirement Specifications) : pure english document talks about specs of functions and have redundent informations

3. Basic SW integration Testing Role  
this role involve a dummy data inputed to a certain module to make sure it is behaves good with other modules without any bugs

4. Debugging & Issues Resolving Role  
this role involve real time testing and maintenance issues that is need to be debugged to find a real world bug or a real time bug after manifacturing to provide a software update of to find a hardware problem to solve in new versions of that ECU

5. RTE generation Role  
the one who generate the RTE and use the main software and runs the code on real time enviroment to check working real world behavior
,such as model based design and just connect things properly to get working application

## Autosar Development Roles

- Application Development  
develope new application and use autosar in application layer,here we exposed to upper layer apis

- Complex Device Drivers development  
develope new drivers for undefined drivers or new drivers that autosar didn't talk about

- I/O hardware abstraction Development  
develope low level I/O abstractions for a certain ECU that is often to develope within the scope of each project requirement changes

- Mcal Development  
develope Mcal for a certain project and is continuously developed according to HW design changes

- Basic SW development & maintenance  
develope Basic SW such as **vector and electrobit**

- tooling  
build tools that help developing configuration and generation tools of a certain software module

## Other Roles

- SW Architect  
the one who distribute roles on teams and define which architecture they will follow

- System Engineer / Requirements Engineer  
the packaging ,mechanical and software that writes the requirements of the overall project to behave in right manner
also make sure that the system is working before deliver the project to the customer

- Autosar Consortium Work Group Active Member  
develope or write a specifications or modify already wrote ones
**active member** the one who have a work load to contribute to the consortium whether writing specs or modifying old ones
**passive member** the one who hasn't a workload or he is a listener in the consortium such as developpers of the autosar who uses autosar specs

- Autosar Expert  
the one who choose controllers and defines which training they will have and actually he can support them by a training also it can be a title

## 5-whys?

before the 5th why you will know the reason of a problem
