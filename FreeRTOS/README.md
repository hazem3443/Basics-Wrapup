# RTOS - Real Time Operating System

why using RTOS ?

- simple apps doesn't need RTOS but with more complex with many periodic jobs RTOS is necessary

- jobs need to have varying execution order (execution threads) with different priority levels

- Minimizing waiting time by executing other jobs instead of just waiting

- managing system resources and shared hardware

## but also we need to consider some points before using RTOS

- requires extra memory overhead

- requires execution time overhead for context switching as well as task scheduling

- porting rtos is not easy, some work only with specific microcontroller and specific toolchain

## Busy-Wait Vs Thread Scheduling

![Busy-Wait VS TaskScheduling](Busy-Wait-VS-ThreadScheduling.png)

- busy-wait depends on waiting each block to finish till the next block execution

- but task scheduling depend on switching between tasks concurrently according to each task priority but only one task at a time such as **RTOS**

- for parallel programming parallel thread execution occurs at the same time on a multi-core processors

![Parallel vs Concurrent](Parallel-concurrent.png)

## Foreground Vs Background

- Foreground program is a program executing now

- Background program is a program interrupted and will be executed after foreground program finishes

- We can consider FreeRtos as a foreground-background system

![ForeGround Vs Background](Fore-back-ground.png)

## Execution Thread

- a sequence of instructions to be executed for doing specific job
- has it's own program start address, PC, SP, CR, Flags
- when stoped or interrupted the thread status is frozen and stored into memory, so it can be restored and the thread execution can be resumed normally
- thread status called context and the memory area callled (thread control block or TCB or context space or thread object)
- single processor can run one thread at a time which called **running state** and other threads are in the **waiting state** waiting for the cpu, Resources or inputs to continue execution.
- RTOS is the piece of the software responsible for managing threads( stop, store, load, start and context switching)

## Thread Control Block

![TCP Diagram](TCP.png)

- each thread context may have priority and name

## Thread States

- thread in **running state** can ask for resources (RTOS call) for only one thread at a time
- RTOS makes the thread go into waiting state when resources are not available
- **waiting state** is associated with the event for which the thread is waiting
- IRQs can trigger some events and RTOS can move a thread from waiting to ready state.
- thread is switched from running to ready when an IRQ triggers high priority thread into ready state.

## Create Thread API

![Create Thread API](Create-Thread_API.png)

- allocating memory for TCB with initial values for PSR,SP, and stack size which we will use later while switching states
- PC value will be set by the thread starting address in flash for this specific thread
- choose a priority for this thread
- TCB located in stack memory in addition to the allocated stack size for this thread
- we need to disable interrupts here
- then we insert this thread to the ready list prioritised
- and if (thread priority < current priority and scheduler is running) we need to insert current running thread into ready state and context switch running thread and move to newly created thread
- then we need to enable IRQ

## thread Lists

- all active threads (waiting and ready) have their thread object in one linkedlist (waiting list or ready list)
- lists shall copy only the address to the thread object not the hole thread object.
- lists shall be ordered by thread priority, so that the scheduler always picks the highest priority thread.
- first node is dummy head contains number of elements in the list

## Arm CM4 OS SUPPORT FEATURES

- **shadowed stack pointer**: **MSP** is used for the os kernel and interrupt handler.**PSP** is used by application tasks.
  - Protects MSP from corruption by application task
  - stack space needed for the ISR and nested interrupt handling is allocated in the main stack only to save memory of saving context of each task while context switching
- **Systick timer**
- **SVC and PendSV** exceptions
  - SVC (SUPERVISOR CALL) Exception
    - used to trigger interrupt with SVC instruction
    - prefered over software interrupts because it generates precise interrupt(handler must execute if not will generate hardfault )
    - can be used by application tasks to request privileged access
  - PENDSV (PENDABLE SERVICE CALL) Exception
    - Triggered by software but not precise
    - Pending status can be set inside a higher priority exception handler
    - making PendSV the lowest exception priority level very usefull, allowing to trigger Context Swtch within interrupts

- **unpreveliged execution level**: security model that restricts the access rights of some application tasks
- **Execlusive access**: useful for semaphores and mutual execlusive

## PendSV for Context Switching

- depend on trigger a flag then come back to the interrupt then make a context switching according to that trigger

![PENDSV FOR CONTEXT SWITCHING](PENDSV_FOR_CONTEXT_SWITCHING.png)

## PendSV to partition an interrupt

- depend executing a high critical part into an interrupt and moving low critical part to PendSV and after finishing high critical part in an interrupt we trigger a PendSV call then execute low critical part that can be interrupted by other high critical sections

![PendSV to partition an interrupt](Partition_AN_INTERRUPT.png)

Till now we know the overview of our OS and how it will work now let's get into some code

## Architectural Steps Toward OS creation

### 1. [**Threads Create and TCP**](#threads-create-and-tcp)

### 2. [**Scheduling and Mutual Execlusion**](#scheduling-and-mutual-execlusion)

### 3. [**Mutex, Semaphore and MailBox**](#mutex-semaphore-and-mailbox)

### 4. [**Timer Support**](#timer-support)

### 5 [**other Features and Events**](#other-features-and-events)

Now let's start with our kit stm32f1 and let's build and debug c code alongside with assembly code and for some architectural organization notes we will create a new folder inside aour advanced project alongside with inc and src inside core folder and inside this file we will create a inc and src folder for our rtos and assebly files will be longside with .c files.

## **Threads Create and TCP**

- here we will use a circular-doubly statically linked list and you need to know about ISA and thumb instructions for our assembly files.

- our RTOS will use SVC, PendSV and Systic interrupts, we will force the application tasks to modify any interrupt priority except those 3 that our rtos uses

- also we will use msp for our RTOS and psp for each task

let's start by our structures we will use for each event-list and thread

### **main Structures**

- Thread structure

```C
  typedef struct thread_t
  {
    uint32_t pStackPointer;        /**< Stack pointer */
    uint32_t priority;             /**< Thread priority */
    RTOS_listItem_t item;          /**< List item of this thread */
  } RTOS_thread_t;
```

  1. TCP pointer which is 16 word starting at the top of the stack of this thread
  
  2. thread priority
  
  3. thread item (not item pointer :D) which will point to the thread item structure which will be linked to a list and point to a pointer to function of our TASKx Thread and next and prev items in the list we can consider this as a pointer to a list items of a circular-doubly linked list

- Thread Stack structure

```C
  typedef struct
  {
    uint64_t stack[THREAD_STACK_SIZE];  /**< Thread stack */
  } RTOS_stack_t;
```

  1. a thread stack with THREAD_STACK_SIZE of 1024 place of 64bit type means 1024 double word means 1024*8 = 8Kbytes for each thread

  note for our stm32f1 we can't use more than 7 threads
  thus we need to set THREAD_PRIORITY_LEVELS to 2

  if we need to use more we need to decrease stack size

- Thread Item structure

```C
  struct listItem_t
  {
    struct listItem_t * pNext;     /**< Pointer to the next list item */
    struct listItem_t * pPrev;     /**< Pointer to the previous list item */
    void * pThread;                /**< Pointer to the thread of the item */
    void * pList;                  /**< Pointer to the list in which the item it */
  };
  typedef struct listItem_t RTOS_listItem_t;
```

  1. pNext pointer pointeing to next item in the list
  2. pPrev pointer pointeing to previous item in the list
  3. pointer to the thread Task Function defined in the main.c as application Task
  4. pointer to list where the item exists (for our RTOS may be Ready ,Waiting, or suspended list and the running will be only one item not a list)

- End Thread Item

```C
typedef struct
{
  RTOS_listItem_t * pNext;     /**< Pointer to the next list item */
  RTOS_listItem_t * pPrev;     /**< Pointer to the previous list item */
} RTOS_listEnd_t;
```
  
  thread end item to save memory for each list head by creating an end type and not depending on **listItem_t** with null value for pThread :D (optimization issue here notice below)
  
  no need for list pointer because this item points to items assigned to a list and only used to interface list start to list end which can be ignored to save memory for each list.

  1. pNext pointer pointeing to next item in the list
  2. pPrev pointer pointeing to previous item in the list
  
- RTOS List

```C
  typedef struct
  {
    uint32_t numOfItems;           /**< Number of threads items in the list */
    RTOS_listItem_t * pIndex;        /**< Pointer to the current item */
    RTOS_listEnd_t listEnd;          /**< List end */
  } RTOS_list_t;
```

  1. number of items in this list
  2. pointer to current item in the list
  3. list end item

let's see some examples by graph

![empty list](empty-list.png)

![one-item in the list](one-iteminthelist.png)

![two-item in the list](two-iteminthelist.png)

then let's get to our main functions

### **main Functions for Task Creation and Deletion**

  you can look at it's implementation in file **rtos_list.c**

  1. RTOS_listInit function
    used to initialize each list with end item in it
  2. RTOS_listInsertEnd function
    used to add item at pIndex of the list
  3. RTOS_listRemove
    used to remove item from the list
  
### functions of RTOS thread

first we need to create ready list which is an array of type list of priority levels size

and top priority item to indicate the current top priority exists we can consider this as a variable containing the current highest priority

```C
  static RTOS_list_t readyList[THREAD_PRIORITY_LEVELS];
  
  static uint32_t currentTopPriority = (THREAD_PRIORITY_LEVELS - 1);

```

then we need to indicate a pointer to the curent running thread

```C
  RTOS_thread_t * pRunningThread;
```

then we have 3 main thread functions

1. **RTOS_threadInitLists** function
  this function initializes each list item by an empty list with **endItem**
2. **RTOS_threadCreate** function  

  ![TCP inside stack allocated for a task](TCB_inside_Stack_Block.png)

  this function starts with validating it's input values then
    - assign stack pointer of the thread which will be after thread TCP we can find this by knowing that we have stack size of 8kbytes and 18 word then thread-sp = sp + size*8 - 18*4
    - also TCP consists of exception return at the end to identify which stack is used msp or psp and return to FPU or not while context switching
    - also this function is going to be called from the SVC handler function
3. **RTOS_threadGetCurrentReady** function
  this function is going to get the highest priority(lowest index in the ready list) thread in the ready list

### some notice here for our RTOS

- our create thread function calls svc function that is going to trigger an interrupt and stack all create function parameters into main stack pointer then the interrupt reads the svc command parameter from **LR** register then save current **LR** to **execReturn** variable then call SVC main handler function which is going to check the SVC operation according to svc immediate argument then calls it's function which will be RTOS create thread function with arguments from the main stack pointer pointing to TCB of current scope at svc create thread function :D.

- while command **svc 1** we have a context switching that pushes all the current r0 to r3 into main stack pointer that we will use while calling the function inside the SVC interrupt handler which can be fetched from main stack pointer pushed while svc call which enables us to retrieve input parameters of the function calling svc command

- also we need to notice that immediate value of svc command can be retrieved from a link register **LR** to identify operation that user asks for which we will handle inside our RTOS kernal so users or tasks can't execute kernal or access any resource without kernal command privilege so application tasks can focus on app logic

- shifting can represent digits we need to pass in order to access a certain location in memory so we need to access 0,1,2,3,.... which will apply to locations or bytes 0,4,8,12,... accordingly so we can shift by 2 meaning multiplying by 4 operation which will apply to 1<<2,2<<2,3<<2,.... respectively this technique is used in stack pointer TCB while creating a thread so keep going there is more comming :D.

---

## **Scheduling and Mutual Execlusion**

### Priority based scheduler

- scheduler is the part od the kernel responsible for determining which thread will run next , most real time kernels are **priority based**.
- types of the priority based kernels : **preemptive and non-preemptive**
- when many threads have the same priority, scheduler can use **round-robin scheduling** allowing equal share of the CPU.
![Round Robin Schedule Example](Round_Robin_Schedule_Example.jpg)

#### non-Preemptive (COOPERATIVE) kernel

- require that each task does something to explicitly give up control of the CPU. thread cooperate with each other to share the CPU.
- low interrupt latency
- non-reentrant functions can be used
- less need to guard shared resources
- lower responsiveness, not recommended for real time applications

![Non Preemptive Kernel](Non-Preemptive-Kernel.png)

#### Preemptive Kernel

- very **high system responsiveness**, most of RTOS kernels are preemptive.
- Highest priority thread ready to run is always given control of the cpu
- current **thread is preempted** when a higher priority thread is ready
- **non-reentrant functions shall not used** without execlusive access such as swapping function if interrupt change values then swapping will be corrupted so we can call swap function a non-reentrant function which means we can't enter and renter again because of interrupts which will corrupt its resources and we need to use execlusive access such as mutexes and semaphores
- lower priority threads may never be run (**starvation**) because of high priority task keep comming over and over.  

![Preemptive Kernel](Preemptive-Kernel.png)

- **DeadLock** may cause corruption to high priority access which cause high priority task to fail.

---

## **Mutex, Semaphore and MailBox**

### Mutual Execlusion

- Two or more threads may want to use **non sharable hardware**, or accessing **shared memory** simultaneously.
- atomic operation can solve the problem, but no processor can update a memory location with one instruction.
- one way to use critical sections (threads can not preempt) when accessing shared resources.
- critical sections is the piece of code which access shared resources.
- critical sections can be implemented by disabling interrupts, which could increased interrupt latency.

### **MUTEX**

- flag that can be tested and updated atomically
- mutex has two states
  - 1 (no thread in the critical section)
  - 0 (one thread in the critical section)
- each thread checks the mutex before entering the critical section, if the mutex is 1, the thread sets the mutex to 0 (mutex lock) and enters the critical section and back to 1 (mutex release) after leaving.

- MUTEX implementation using ARM CM4 synchronization primitives
  - non-blocking mechanisms that a thread or process can use to obtain execlusive access to a memory location
  - using Load(LDREX) and store(STREX) register execlusive instructions
  - load and store with exclusive operation used as pair with the same address
  - if a store-execlusive instruction performs the store, it writes 0 to its register if it does not perform the store, it writes 1.
  - while execlusive operations **LDREX and STREX** a local monitor is watching the **LDREX** operand1 (R0) so if any one trying to access it in a new thread or interrupt or another CPU-core it will write (STORE at **STREX**) 1 not the **operand2** of STREX command to it in the other(second) scope which will not lock the mutex and will wait to first thread or core to finish
  - we can disable interrupts before and enable it after but this will increase interrupt latency(decrease system responsiveness) and will not be suitable for multicore processor
  - MUTEX implementation in RTOS
    - if a thread is not able to lock a mutex, RTOS shall freeze its context, move it into waiting/blocked list and trigger context switching
    - the scheduler shall run the next high priority ready thread
    - whenever the mutex got released, RTOS shall wake up the blocked thread and move it into ready list and trigger context switching.
    - Mutex lock and release operations are RTOS responsibility and shall be implemented using RTOS calls.

### **Semaphore**
  
- Resources can be shared between limited number of threads
- Mutex is a binary flag and can be extended to a counter to support access from multiple threads.
- semaphore is functionally similar to the mutex but with counter
- mutex is considered a binary semaphore

### **Mailbox**

- used for interthread communication, unlike semaphores which provide only synchronization with information exchange.
- using shared buffers, one thread can fill the buffer(provider),the other empties it(consumer).
- the consumer needs to wait when the buffer is empty and the producer need to wait when the buffer is full.
- shared buffer needs to be updated by the producer and consumer mutually execlusively, so mutex is need for mutual exclusive access to the buffer and semaphore for counting number of messages in the buffer.
- buffer has limited size, producer can not fill the buffer infinitely, so another semaphore is needed for counting the empty slots in the buffer.
- can be implemented using queue and number of data in queue can be represented by semaphore.

---

## **Timer Support**

---

## **other Features and Events**
