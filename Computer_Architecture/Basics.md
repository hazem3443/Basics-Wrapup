# Basics

## **Computer Organization**

is concerned with the way the hardware components operate and the way they are connected together to form the computer system.

## von Neumann architecture **VS** Harvard architecture

- The **von Neumann architecture** describes a general framework, or structure, that a computer's hardware, programming, and data should follow. Although other structures for computing have been devised and implemented, the vast majority of computers in use today operate according to the von Neumann architecture.

    von Neumann envisioned the structure of a computer system as being composed of the following components:

  1. ALU: The Arithmetic-Logic unit that performs the computer's computational and logical functions.

  2. RAM: Memory; more specifically, the computer's main, or fast, memory, also known as Random Access Memory(RAM).

  3. Control Unit: This is a component that directs other components of the computer to perform certain actions, such as directing the fetching of data or instructions from memory to be processed by the ALU; and

  4. Man-machine interfaces; i.e. input and output devices, such as keyboard for input and display monitor for output.

    ![Von neumann diagram](https://static.studytonight.com/computer-architecture/images/digital-computers-1.png)

    An example of computer architecture base on the von Neumann architecture is **the desktop personal computer**.

- **Harvard architecture**
The Harvard architecture uses physically separate storage and signal pathways for their instructions and data. The term originated from the Harvard Mark I and the data in relay latches (23- digits wide).

    In a computer with Harvard architecture, the CPU can read both an instruction and data from memory at the same time, leading to double the memory bandwidth.

    Microcontroller(single-chip microcomputer)-based computer systems and DSP(Digital Signal Processor)-based computer systems are examples of Harvard architecture.

**RAM**: Random Access Memory
**DRAM**: Dynamic RAM, is made of capacitors and transistors, and must be refreshed every 10~100 ms. It is slower and cheaper than SRAM.
SRAM: Static RAM, has a six transistor circuit in each cell and retains data, until powered off.
**NVRAM**: Non-Volatile RAM, retains its data, even when turned off. Example: Flash memory.
ROM: Read Only Memory, is non-volatile and is more like a permanent storage for information. It also stores the bootstrap loader program, to load and start the operating system when computer is turned on. PROM(Programmable ROM), EPROM(Erasable PROM) and EEPROM(Electrically Erasable PROM) are some commonly used ROMs.

**SISD (Single Instruction Stream, Single Data Stream)**
It represents the organization of a single computer containing a control unit, processor unit and a memory unit. Instructions are executed sequentially. It can be achieved by pipelining or multiple functional units.

**SIMD (Single Instruction Stream, Multiple Data Stream)**
It represents an organization that includes multiple processing units under the control of a common control unit. All processors receive the same instruction from control unit but operate on different parts of the data.

They are highly specialized computers. They are basically used for numerical problems that are expressed in the form of vector or matrix. But they are not suitable for other types of computations

**MISD (Multiple Instruction Stream, Single Data Stream)**
It consists of a single computer containing multiple processors connected with multiple control units and a common memory unit. It is capable of processing several instructions over single data stream simultaneously. MISD structure is only of theoretical interest since no practical system has been constructed using this organization.

**MIMD (Multiple Instruction Stream, Multiple Data Stream**
It represents the organization which is capable of processing several programs at same time. It is the organization of a single computer containing multiple processors connected with multiple control units and a shared memory unit. The shared memory unit contains multiple modules to communicate with all processors simultaneously. Multiprocessors and multicomputer are the examples of MIMD. It fulfills the demand of large scale computations.

**What is Pipelining?**

Pipelining is a technique where multiple instructions are overlapped during execution. Pipeline is divided into stages and these stages are connected with one another to form a pipe like structure. Instructions enter from one end and exit from another end.

Pipelining increases the overall instruction throughput.

In pipeline system, each segment consists of an input register followed by a combinational circuit. The register is used to hold data and combinational circuit performs operations on it. The output of combinational circuit is applied to the input register of the next segment.

**Types of Pipeline**
It is divided into 2 categories:

1. Arithmetic Pipeline
2. Instruction Pipeline

**Arithmetic Pipeline**
Arithmetic pipelines are usually found in most of the computers. They are used for floating point operations, multiplication of fixed point numbers etc. For example: The input to the Floating Point Adder pipeline is:

X = A*2^a
Y = B*2^b
Here A and B are mantissas (significant digit of floating point numbers), while a and b are exponents.

The floating point addition and subtraction is done in 4 parts:

1. Compare the exponents.

2. Align the mantissas.

3. Add or subtract mantissas

4. Produce the result.

**Instruction Pipeline**
In this a stream of instructions can be executed by overlapping fetch, decode and execute phases of an instruction cycle. This type of technique is used to increase the throughput of the computer system.

An instruction pipeline reads instruction from the memory while previous instructions are being executed in other segments of the pipeline. Thus we can execute multiple instructions simultaneously. The pipeline will be more efficient if the instruction cycle is divided into segments of equal duration.

**Pipeline Conflicts**
things that cause the pipeline to deviate its normal performance.

1. Timing Variations
All stages cannot take same amount of time. This problem generally occurs in instruction processing where different instructions have different operand requirements and thus different processing time.

2. Data Hazards
When several instructions are in partial execution, and if they reference same data then the problem arises. We must ensure that next instruction does not attempt to access data before the current instruction, because this will lead to incorrect results.

3. Branching
In order to fetch and execute the next instruction, we must know what that instruction is. If the present instruction is a conditional branch, and its result will lead us to the next instruction, then the next instruction may not be known until the current one is processed.

4. Interrupts
Interrupts set unwanted instruction into the instruction stream. Interrupts effect the execution of instruction.

5. Data Dependency
It arises when an instruction depends upon the result of a previous instruction but this result is not yet available.

### Advantages of Pipelining

1. The cycle time of the processor is reduced.
2. It increases the throughput of the system
3. It makes the system reliable.

### **Disadvantages of Pipelining**

1. The design of pipelined processor is complex and costly to manufacture.
2. The instruction latency is more.

### Vector(Array) Processing and Superscalar Processors

A Scalar processor is a normal processor, which works on simple instruction at a time, which operates on single data items. But in today's world, this technique will prove to be highly inefficient, as the overall processing of instructions will be very slow.

**What is Vector(Array) Processing?**
some problems require vast number of computations on multiple data items, that will take a conventional computer(with scalar processor) days or even weeks to complete.

Such complex instructions, which operates on multiple data at the same time, requires a better way of instruction execution, which was achieved by Vector processors.

Scalar CPUs can manipulate one or two data items at a time, which is not very efficient. Also, simple instructions like ADD A to B, and store into C are not practically efficient.

Addresses are used to point to the memory location where the data to be operated will be found, which leads to added overhead of data lookup. So until the data is found, the CPU would be sitting ideal, which is a big performance issue.

In vector processor a single instruction, can ask for multiple data operations, which saves time, as instruction is decoded once, and then it keeps on operating on different data items.

**Applications of Vector Processors**
Computer with vector processing capabilities are in demand in specialized applications. The following are some areas where vector processing is used:

1. Petroleum exploration.
2. Medical diagnosis.
3. Data analysis.
4. Weather forecasting.
5. Aerodynamics and space flight simulations.
6. Image processing.
7. Artificial intelligence.

### Superscalar Processors

It was first invented in 1987. It is a machine which is designed to improve the performance of the scalar processor. In most applications, most of the operations are on scalar quantities. Superscalar approach produces the high performance general purpose processors.

The main principle of superscalar approach is that it executes instructions independently in different pipelines. As we already know, that Instruction pipelining leads to parallel processing thereby speeding up the processing of instructions. In Superscalar processor, multiple such pipelines are introduced for different operations, which further improves parallel processing.

**A scalar processor** works on one or two data items, while the **vector processor** works with multiple data items. A **superscalar processor** is a combination of both. Each instruction processes one data item, but there are multiple execution units within each CPU thus multiple instructions can be processing separate data items concurrently.

**The superscalar technique is associated with some characteristics**, these are:

1. Instructions are issued from a sequential instruction stream.
2. CPU must dynamically check for data dependencies.
3. Should accept multiple instructions per clock cycle.

### I/O Organization

- **Peripheral Devices**
Input or output devices that are connected to computer are called peripheral devices.

- **Interfaces**

Interface is a shared boundary between two separate components of the computer system which can be used to attach two or more components to the system for communication purposes.

There are two types of interface:

1. CPU Inteface
2. I/O Interface

Let's understand the I/O Interface in details,

**Input-Output Interface**
Peripherals connected to a computer need special communication links for interfacing with CPU. In computer system, there are special hardware components between the CPU and peripherals to control or manage the input-output transfers. These components are called input-output interface units because they provide communication links between processor bus and peripherals. They provide a method for transferring information between internal system and input-output devices.

### Hardware Interrupts

When the signal for the processor is from an external device or hardware then this interrupts is known as hardware interrupt.

Let us consider an example: when we press any key on our keyboard to do some action, then this pressing of the key will generate an interrupt signal for the processor to perform certain action. Such an interrupt can be of two types:

1. Maskable Interrupt
The hardware interrupts which can be delayed when a much high priority interrupt has occurred at the same time.

2. Non Maskable Interrupt
The hardware interrupts which cannot be delayed and should be processed by the processor immediately.

### Software Interrupts

The interrupt that is caused by any internal system of the computer system is known as a software interrupt. It can also be of two types:

1. Normal Interrupt
The interrupts that are caused by software instructions are called normal software interrupts.

2. Exception
Unplanned interrupts which are produced during the execution of some program are called exceptions, such as division by zero.

### Daisy Chaining Priority

This way of deciding the interrupt priority consists of serial connection of all the devices which generates an interrupt signal. The device with the highest priority is placed at the first position followed by lower priority devices and the device which has lowest priority among all is placed at the last in the chain.

In daisy chaining system all the devices are connected in a serial form. The interrupt line request is common to all devices. If any device has interrupt signal in low level state then interrupt line goes to low level state and enables the interrupt input in the CPU. When there is no interrupt the interrupt line stays in high level state. The CPU respond to the interrupt by enabling the interrupt acknowledge line. This signal is received by the device 1 at its PI input. The acknowledge signal passes to next device through PO output only if device 1 is not requesting an interrupt.

The following figure shows the block diagram for daisy chaining priority system.

![daisy chaining priority Interrupts](https://static.studytonight.com/computer-architecture/images/priority-interrupt-1.png)

**What is Interleaved Memory?**

It is a technique for compensating the relatively slow speed of DRAM(Dynamic RAM). In this technique, the main memory is divided into memory banks which can be accessed individually without any dependency on the other.

For example: If we have 4 memory banks(4-way Interleaved memory), with each containing 256 bytes, then, the Block Oriented scheme(no interleaving), will assign virtual address 0 to 255 to the first bank, 256 to 511 to the second bank. But in Interleaved memory, virtual address 0 will be with the first bank, 1 with the second memory bank, 2 with the third bank and 3 with the fourt, and then 4 with the first memory bank again.

Hence, CPU can access alternate sections immediately without waiting for memory to be cached. There are multiple memory banks which take turns for supply of data.

**Memory interleaving is a technique for increasing memory speed. It is a process that makes the system more efficient, fast and reliable.**

For example: In the above example of 4 memory banks, data with virtual address 0, 1, 2 and 3 can be accessed simultaneously as they reside in spearate memory banks, hence we do not have to wait for completion of a data fetch, to begin with the next.

**Types of Interleaving**
There are two methods for interleaving a memory:

- **2-Way Interleaved**
Two memory blocks are accessed at same time for writing and reading operations.

- **4-Way Interleaved**
Four memory blocks are accessed at the same time.

## RISC and CISC Processors

### RISC Processor

- It is known as Reduced Instruction Set Computer.
- It is a type of microprocessor that has a limited number of instructions.
- They can execute their instructions very fast because instructions are very small and simple.

- RISC chips require fewer transistors which make them cheaper to design and produce.
- In RISC, the instruction set contains simple and basic instructions from which more complex instruction can be produced.
- Most instructions complete in one cycle, which allows the processor to handle many instructions at same time.

In this instructions are register based and data transfer takes place from register to register.

### CISC Processor

- It is known as Complex Instruction Set Computer.
- It was first developed by Intel.
- It contains large number of complex instructions.
- In this instructions are not register based.
- Instructions cannot be completed in one machine cycle.
- Data transfer is from memory to memory.
- Micro programmed control unit is found in CISC.
- Also they have variable instruction formats.

### **Difference Between CISC and RISC**

| Architectural Characterstics |                       Complex Instruction Set Computer(CISC)                       |                Reduced Instruction Set Computer(RISC) |
| ---------------------------- | :--------------------------------------------------------------------------------: | ----------------------------------------------------: |
| Instruction size and format  |   Large set of instructions with variable formats (16-64 bits per instruction).    | Small set of instructions with fixed format (32 bit). |
| Data transfer                |                                 Memory to memory.                                  |                                 Register to register. |
| CPU control                  | Most micro coded using control memory (ROM) but modern CISC use hardwired control. |              Mostly hardwired without control memory. |
| Instruction type             |                          Not register based instructions.                          |                          Register based instructions. |
| Memory access                |                                More memory access.                                 |                                   Less memory access. |
| Clocks                       |                               Includes multi-clocks.                               |                                Includes single clock. |
| Instruction nature           |                             Instructions are complex.                              |                  Instructions are reduced and simple. |
