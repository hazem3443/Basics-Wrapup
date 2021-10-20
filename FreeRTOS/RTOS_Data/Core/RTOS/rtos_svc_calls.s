

.syntax unified
.cpu cortex-m3
.thumb

.global RTOS_SVC_schedulerStart
.global RTOS_SVC_threadCreate

.text

.type RTOS_SVC_schedulerStart, %function
RTOS_SVC_schedulerStart:
    svc 0
    bx lr

.type RTOS_SVC_threadCreate, %function
RTOS_SVC_threadCreate:
    svc 1
    bx lr


