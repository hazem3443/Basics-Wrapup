
.syntax unified
.cpu cortex-m3
.thumb

.global RTOS_SVC_Handler
.global RTOS_PendSV_Handler

.text

.type RTOS_SVC_Handler, %function
RTOS_SVC_Handler:
    tst lr, #4                /* Test bit 2 of the link register to find current stack lr&0b100 and to see the results look at zero flag in xPSR */
    ite eq                    /* eq when zero flag is set --- eq means z flag=1 and ite means next two instructions are conditional */
    mrseq r0, msp             /* msp when bit 2 is cleared */
    mrsne r0, psp             /* psp when bit 2 is set */
    ldr r1,=svcEXEReturn      /* Load the address of svcEXEReturn in r1 */
    str lr,[r1]               /* Store lr in svcEXEReturn */
    bl RTOS_SVC_Handler_main  /* Run C part of SVC Handler */
    ldr r1,=svcEXEReturn      /* Load the address of svcEXEReturn in r1 */
    ldr lr,[r1]               /* Load lr with updated svcEXEReturn value */
    bx lr                     /* Return from interrupt */

.type RTOS_PendSV_Handler, %function
RTOS_PendSV_Handler:
    /* ******************** */
    /* Save current context */
    /* ******************** */
    mrs r1, psp               /* Store psp in r1 */
//  tst lr, #0x10             /* Test bit 4. if zero, need to stack floating point regs */
//  it eq                     /* eq means zero flag is set */
//  vstmdbeq r1!, {s16-s31}   /* save floating point registers */
    mov r2, lr                /* Store lr in r2 */
    mrs r3, control           /* Store control in r3 */
    stmdb r1!,{r2-r11}        /* Store multiple registers (r2 to r11).
                                 Decrement address before each access. ! for write back into address of r1 which will be in stack of this thread scope*/
    bl RTOS_threadGetRunning  /* Get current running thread location */
    str r1,[r0]               /* Store the stack pointer for the current thread  */
    /* ******************** */
    /* Load next context    */
    /* ******************** */
    mov r0, #1                   /* Put 1 in r0 */
    msr basepri, r0              /* Disable interrupts with priority 1 and greater */
    bl RTOS_threadSwitchRunning  /* Change current running thread */
    mov r0, #0                   /* Put 0 in r0 */
    msr basepri, r0              /* Enable interrupts */
    bl RTOS_threadGetRunning     /* Get current running thread location */
    ldr r1,[r0]                  /* Get its value which is the stack pointer */
    ldmia r1!,{r2-r11}           /* Load multiple registers (r2 to r11).
                                    Increment address after each access. ! for write back */
    mov lr, r2                   /* Load lr with value from r2 */
    msr control, r3              /* Load control with value from r3 */
    isb                          /* Instruction Synchronization Barrier, recommended after control change */
//  tst lr, #0x10                /* Test bit 4. If zero, need to unstack floating point regs */
//  it eq                        /* eq means zero flag is set */
//  vldmiaeq r1!, {s16-s31}      /* Load floating point registers */
    msr psp, r1                  /* set psp to the stack pointer of the new current task */
    bx lr                        /* Return */
