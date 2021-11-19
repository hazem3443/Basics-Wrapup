/*******************************************************************************
 * @file    rtos_thread.c
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    15 Jul 2019
 *          
 * @brief   RTOS Thread
 * @note    
 *
@verbatim
Copyright (C) Almohandes.org, 2019

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
@endverbatim
*******************************************************************************/

/* Includes */
#include "Inc/rtos.h"

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @defgroup rtos_thread
 * @brief
 * @{
 */

/**
 * @defgroup rtos_thread_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_variables
 * @{
 */

/**
 * @brief   Ready list for the threads waiting for the execution,
 *          arranged by priority.
 */
static RTOS_list_t readyList[THREAD_PRIORITY_LEVELS]; //array of lists ordered by priority levels

/**
 * @brief   Timer list for the threads waiting, arranged by timeout value.
 */
static RTOS_list_t timerList;//will be ordered according to timeout value

/**
 * @brief   Current top priority.
 */
static uint32_t currentTopPriority = (THREAD_PRIORITY_LEVELS - 1);

/**
 * @brief   Currently running thread pointer.
 */
RTOS_thread_t * pRunningThread;

/**
 * @brief   Currently running thread ID.
 */
static uint32_t runningThreadID = 0;

/**
 * @brief   Number of threads
 */
static uint32_t numOfThreads = 0;

/**
 * @brief   Variable to store millisecond ticks
 */
static volatile uint32_t sysTickCounter = 0;

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_functions
 * @{
 */

/**
 * @brief   Initialize thread list
 * @note
 * @param
 * @retval  None
 */
void RTOS_threadInitLists(void)
{
  /* Initialize ready list */
  for(uint32_t priority = 0; priority < THREAD_PRIORITY_LEVELS; priority++)
  {
    RTOS_listInit(&readyList[priority]);
  }
  /* Initialize timer list */
  RTOS_listInit(&timerList);
}

/**
 * @brief   Creates new thread.
 * @note
 * @param   RTOS_thread_t *, RTOS_stack_t *, uint32_t, void *, char *
 * @retval  None
 *
 * first parameter will contain the thread structure block in the bss section
 * second will contain the end of stack block in the bss section
 * third will contain the priority as number
 * fourth the function address in flash
 *
 * 0x2000 0000 .bss which will contain the stack of each thread which will be allocated by compiler
 *
 * 0x2000 0058 thread-pointer
 * 0x2000 0078 thread-stack-end-pointer
 * ....
 * 0x2000 0078 +512*8(0x400) = 0x2000 1078  thread-stack-start-pointer
 * ...
 * 0x2005 0000 ->MSP
 *
 *
 *some times the function need to save it's LR in stack in order to identify it's working stack scope before branching
 *
 *this function is going to initiate the thread block and attach it to it's item in a ready list at a certain priority index in the ready list
 */
void RTOS_threadCreate(RTOS_thread_t * pThread, RTOS_stack_t * pStack,
    uint32_t priority, void * pFunction)
{
  /* Check input parameters */
  ASSERT(NULL != pThread);
  ASSERT(NULL != pStack);
  ASSERT(THREAD_PRIORITY_LEVELS > priority);
  ASSERT(NULL != pFunction);

  /* Create stack frame, size multiplied with 8 for the double word
   * length converted to byte length, stack f16<<4 =rame size is 18 words */
  pThread->pStackPointer = ((uint32_t)pStack + (THREAD_STACK_SIZE * 8) - (18 * 4));

  /*---shifting technique
   * shifting by 2 means shift the current number by 2 steps of pStackPointer type which is uint_32
   * this mean
   * 0->0
   * 1->4
   * 2->8
   * 3->12
   * 4->16
   * 5->20
   *
   * which represent multiplying by 4
   * which means
   * <<1 means *2
   * <<2 means *4
   * <<3 means *8
   * <<4 means *16
   *
   * in our example 16<<2 in decimal domain means *4
   * which means 16<<2 = 16*4 = 64
   * and 17<<2 = 17*4 = 68
   * and 1<<2 = 1*4 = 4
   *
   * and in our stack we casted the input pointer into 32 bit and save our data as
   bytes in a uint32 space for each record in our TCP inside our stack

   because 18 record of uint_32 size
   from address 0*4=0 to 4*17=68
   so we need to shift by 2 = <<2 for each register index inside TCP inside the stack inputed to this function
   * */
  /* Write thread function into return address [PC]*/
  MEM32_ADDRESS((pThread->pStackPointer + (16 << 2))) = (uint32_t) pFunction;

  /* Write initial xPSR, program status register, thumb */
  MEM32_ADDRESS((pThread->pStackPointer + (17 << 2))) = 0x01000000;

  /* Write EXC_RETURN, since the execution threads are using PSP, this will
   * allow SVC to return to the thread with PSP
   * F9 means MSP
   * FD means PSP
   * */
  MEM32_ADDRESS(pThread->pStackPointer) = 0xFFFFFFFDUL;

  /* Write initial CONTROL register value UNPRIVILEGED, PSP & no FPU */
  MEM32_ADDRESS((pThread->pStackPointer + (1 << 2))) = 0x3;

  /* Set thread priority */
  pThread->priority = priority;

  /* Increment number of threads and set the thread ID we made that check only to know if this thread was previously created in order to
   * set its id or not*/
  if (0 == pThread->threadID)
  {
	  pThread->threadID = ++numOfThreads;
  }
  else
  {
	  /* Do nothing, this thread was re-created */
  }

  /* Thread is not yet in any list */
  pThread->genericListItem.pList = NULL;
  pThread->eventListItem.pList = NULL;

  /* Link this thread with its list item */
  pThread->genericListItem.pThread = (void *)pThread;
  pThread->eventListItem.pThread = (void *)pThread;

  /* Set item value to the priority -- extra ordering value to order items with the same priority*/
  pThread->eventListItem.itemValue = priority;

  /* Add new thread to ready list */
  RTOS_threadAddToReadyList(pThread);
}

/**
 * @brief   Destroys a thread
 * @note
 * @param   RTOS_thread_t *
 * @retval  None
 */
void RTOS_threadDestroy(RTOS_thread_t *pThread)
{
  /* Check input parameters */
  ASSERT(NULL != pThread);

  /* Check if the generic list item in any list */
  if (NULL != pThread->genericListItem.pList)
  {
    /* Remove the generic list item from the current list */
    RTOS_listRemove(&pThread->genericListItem);
  }
  else
  {
    /* Do nothing, generic list item is not in any list */
  }

  /* Check if the event list item in any list */
  if (NULL != pThread->eventListItem.pList)
  {
    /* Remove the event list item from the current list */
    RTOS_listRemove(&pThread->eventListItem);
  }
  else
  {
    /* Do nothing, event list item is not in any list */
  }

  /* Check if the removed thread is the current thread */
  if (pThread == pRunningThread)
  {
    /* The current thread will be removed, request context switch  */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
  }
  else
  {
    /* Do nothing */
  }
}

/**
 * @brief   Get current highest priority in ready list
 * @note
 * @param
 * @retval  RTOS_thread_t *
 */
RTOS_thread_t * RTOS_threadGetRunning(void)
{
  return pRunningThread;
}

/**
 * @brief   Switch the current running thread
 * @note
 * @param
 * @retval  None
 */
void RTOS_threadSwitchRunning(void)
{
  /* Find highest priority ready thread */
  while (0 == readyList[currentTopPriority].numOfItems)
  {
	/* Check current top priority not greater than the maximum */
	ASSERT(THREAD_PRIORITY_LEVELS > currentTopPriority);

	/* No threads with the current top priority,
	 * increment current top priority */
	currentTopPriority++;
  }

  /* Threads are found, update list index to the next thread */
  RTOS_list_t *pReadyList = &readyList[currentTopPriority];
  pReadyList->pIndex = pReadyList->pIndex->pNext;

  /* Check if the new index pointing to the end of the list */
  if(pReadyList->pIndex == (RTOS_listItem_t *)&pReadyList->listEnd)
  {
	/* Get the next thread */
	pReadyList->pIndex = pReadyList->pIndex->pNext;
  }
  else
  {
	/* Do nothing, index is not pointing to the end */
  }

  /* Update global current running thread */
  pRunningThread = (RTOS_thread_t *)pReadyList->pIndex->pThread;

  /* Update current running thread */
  runningThreadID = pRunningThread->threadID;
}

/**
 * @brief   Add thread to the ready list
 * @note
 * @param
 * @retval  None
 */
void RTOS_threadAddToReadyList(RTOS_thread_t *pThread)
{
  /* Check input parameters */
  ASSERT(NULL != pThread);

  /* Add new thread to ready list */
  RTOS_listInsertEnd(&readyList[pThread->priority], &pThread->genericListItem);

  /* Set current top priority */
  if (pThread->priority < currentTopPriority)
  {
    currentTopPriority = pThread->priority;
  }

  /* Check the need for context switch when scheduler is running
   * and this thread is the higher priority than the running thread */
  if ((NULL != pRunningThread) && (pThread->priority < pRunningThread->priority))
  {
    /* Trigger context switch, set PendSV to pending */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
  }
  else
  {
    /* Context switch is not required */
  }
}

/**
 * @brief   Refresh the timer list
 * @note
 * @param   None
 * @retval  None
 */
void RTOS_threadRefreshTimerList(void)
{
  /* Pointer to the unblocked thread */
  RTOS_thread_t *pThread;

  /* Check scheduler status */
  if (1 == RTOS_isSchedulerRunning())
  {
    /* Increment SysTick counter */
    ++sysTickCounter;

    /* Check SysTick counter overflow */
    if (0 == sysTickCounter)
    {
      /* TODO: Handle counter overflow */
      ASSERT(0);
    }
    else
    {
      /* No counter overflow, do nothing */
    }

    /* Check if timer list has threads waiting */
    if (0 < timerList.numOfItems)
    {
      /* Timer list is not empty, check timeout values */
      while (sysTickCounter >= timerList.listEnd.pNext->itemValue)
      {
        /* Get first thread waiting */
        pThread = timerList.listEnd.pNext->pThread;

        /* Check returned thread */
        ASSERT(NULL != pThread);

        /* Thread timeout, remove from timer list */
        RTOS_listRemove(&pThread->genericListItem);

        /* Check if the thread waiting for synchronization event */
        if (NULL != pThread->eventListItem.pList)
        {
          /* Remove the thread from the event list */
          RTOS_listRemove(&pThread->eventListItem);
        }
        else
        {
          /* Do nothing, this thread is not in any event lists */
        }

        /* Add the returned thread into ready list */
        RTOS_threadAddToReadyList(pThread);
      }
    }
    else
    {
      /* Timer list is empty, do nothing */
    }
  }
  else
  {
    /* Scheduler is not running, do nothing */
  }
}

/**
 * @brief   Add thread to the timer list
 * @note
 * @param   None
 * @retval  None
 */
void RTOS_threadAddRunningToTimerList(uint32_t waitTime)
{
  /* Check input parameters */
  ASSERT(0 != waitTime);

  /* Temp variable for the wake up tick */
  uint32_t wakeUpTick = 0;

  /* Calculate wake up tick */
  wakeUpTick = sysTickCounter + waitTime;

  /* Check counter overflow */
  if (sysTickCounter > wakeUpTick)
  {
    /* TODO: Handle overflow */
    ASSERT(0);
  }
  else
  {
    /* No overflow, do nothing */
  }

  /* Set generic list item value */
  pRunningThread->genericListItem.itemValue = wakeUpTick;

  /* Remove from ready list */
  RTOS_listRemove(&pRunningThread->genericListItem);

  /* Add to timer list */
  RTOS_listInsert(&timerList, &pRunningThread->genericListItem);

  /* Trigger context switch, set PendSV to pending */
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
