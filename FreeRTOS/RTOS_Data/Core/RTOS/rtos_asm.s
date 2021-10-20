
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
    bx lr                     /* Return */

.type RTOS_PendSV_Handler, %function
RTOS_PendSV_Handler:


    bx lr                        /* Return */
