

.syntax unified
.cpu cortex-m3
.thumb

.global RTOS_SVC_schedulerStart
.global RTOS_SVC_threadCreate

.global RTOS_SVC_mutexCreate
.global RTOS_SVC_mutexLock
.global RTOS_SVC_mutexRelease

.global RTOS_SVC_semaphoreCreate
.global RTOS_SVC_semaphoreTake
.global RTOS_SVC_semaphoreGive

.global RTOS_SVC_mailboxCreate
.global RTOS_SVC_mailboxWrite
.global RTOS_SVC_mailboxRead

.global RTOS_SVC_threadDelay
.global RTOS_SVC_threadDestroy

.text

.type RTOS_SVC_schedulerStart, %function
RTOS_SVC_schedulerStart:
    svc 0
    bx lr

.type RTOS_SVC_threadCreate, %function
RTOS_SVC_threadCreate:
    svc 1
    bx lr

.type RTOS_SVC_mutexCreate, %function
RTOS_SVC_mutexCreate:
    svc 2
    bx lr

.type RTOS_SVC_mutexLock, %function
RTOS_SVC_mutexLock:
    svc 3
    bx lr

.type RTOS_SVC_mutexRelease, %function
RTOS_SVC_mutexRelease:
    svc 4
    bx lr

.type RTOS_SVC_semaphoreCreate, %function
RTOS_SVC_semaphoreCreate:
    svc 5
    bx lr

.type RTOS_SVC_semaphoreTake, %function
RTOS_SVC_semaphoreTake:
    svc 6
    bx lr

.type RTOS_SVC_semaphoreGive, %function
RTOS_SVC_semaphoreGive:
    svc 7
    bx lr

.type RTOS_SVC_mailboxCreate, %function
RTOS_SVC_mailboxCreate:
    svc 8
    bx lr

.type RTOS_SVC_mailboxWrite, %function
RTOS_SVC_mailboxWrite:
    svc 9
    bx lr

.type RTOS_SVC_mailboxRead, %function
RTOS_SVC_mailboxRead:
    svc 10
    bx lr

.type RTOS_SVC_threadDelay, %function
RTOS_SVC_threadDelay:
    svc 11
    bx lr

.type RTOS_SVC_threadDestroy, %function
RTOS_SVC_threadDestroy:
    svc 12
    bx lr
