/*******************************************************************************
 * @file    rtos.c
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    16 Jul 2019
 *          
 * @brief   RTOS Main
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
#include "../RTOS/Inc/rtos.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup rtos
 * @brief
 * @{
 */

/**
 * @defgroup rtos_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_private_variables
 * @{
 */

/**
 * @brief   Variable to store millisecond ticks
 */
static volatile uint32_t sysTickCounter = 0;

/**
 * @brief   Thread and stack object for idle thread
 */
static RTOS_thread_t idleThread;
static RTOS_stack_t idleThreadStack;

/**
 * @}
 */

/**
 * @defgroup rtos_exported_variables
 * @{
 */

/**
 * @brief   EXC_RETURN value used to return from SVC interrupts
 */
uint32_t svcEXEReturn;

/**
 * @}
 */

/**
 * @defgroup rtos_imported_variables
 * @{
 */

static void idleThreadFunction(void);

/**
 * @}
 */

/**
 * @brief   Idle thread function
 * @note
 * @param   None
 * @retval  None
 */
static void idleThreadFunction(void)
{
  while(1)
  {

  }
}
/**
 * @}
 */

/**
 * @defgroup rtos_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_exported_functions
 * @{
 */

/**
 * @brief   RTOS Initialization function
 * @note
 * @param   None
 * @retval  None
 */
void RTOS_init(void)
{
  /* Disable interrupts */
  __disable_irq();

  /* Enable double word stack alignment */
  SCB->CCR |= SCB_CCR_STKALIGN_Msk;

  /* Configure and enable SysTick interrupts */
  ASSERT(0 == SysTick_Config(SYSTEM_CORE_CLOCK_HZ / SYS_TICK_RATE_HZ));

  /* Set priority group to 3
   * bits[3:0] are the sub-priority,
   * bits[7:4] are the preempt priority (0-15) */
  NVIC_SetPriorityGrouping(3);

  /* Set priority levels */
  NVIC_SetPriority(SVCall_IRQn, 0);
  NVIC_SetPriority(SysTick_IRQn, 1);

  /* Set PendSV to lowest possible priority */
  NVIC_SetPriority(PendSV_IRQn, 0xFF);

  /* Enable SVC and PendSV interrupts */
  NVIC_EnableIRQ(PendSV_IRQn);
  NVIC_EnableIRQ(SVCall_IRQn);

  /* Disable all interrupts except SVC */
  __set_BASEPRI(1);

  /* Initialize thread module */
  RTOS_threadInitLists();

  /* Enable interrupts */
  __enable_irq();
}

/**
 * @brief   Start RTOS scheduler
 * @note
 * @param   None
 * @retval  None
 */
void RTOS_schedulerStart(void)
{
  /* Create idle thread */
  RTOS_threadCreate(
	  &idleThread,
	  &idleThreadStack,
	  (THREAD_PRIORITY_LEVELS - 1),
	  idleThreadFunction);

  /* Pointer to the current running thread */
  RTOS_thread_t * pRunningThread;

  /* Update the running thread with the highest priority thread */
  RTOS_threadSwitchRunning();

  /* Get running thread */
  pRunningThread = RTOS_threadGetRunning();

  /* Set SVC interrupt return to the first thread */
  svcEXEReturn = MEM32_ADDRESS(pRunningThread->pStackPointer);

  /* Return to thread with PSP */
  __set_PSP((uint32_t)(pRunningThread->pStackPointer + 10 * 4));

  /* Switch to use Process Stack, unprivileged state */
  __set_CONTROL(MEM32_ADDRESS((pRunningThread->pStackPointer + (1 << 2))));

  /* Execute ISB after changing CONTROL */
  __ISB();

  /* Reset tick counter */
  sysTickCounter = 0;

  /* Enable all interrupts */
  __set_BASEPRI(0);

}

/**
 * @brief   SVC handler main
 * @note
 * @param   uint32_t *
 * @retval  None
 */
void RTOS_SVC_Handler_main(uint32_t * svc_args)
{
  /* Check input parameters */
  ASSERT(NULL != svc_args);

  uint8_t svc_number;

  /* Memory[(Stacked PC)-2] */
  svc_number = ((char *) svc_args[6])[-2];

  /* Temp variables */
  uint32_t returnStatus;

  /* Check svc number */
  switch(svc_number)
  {
    case 0:
      RTOS_schedulerStart();
    break;

    case 1:
      RTOS_threadCreate(
          (RTOS_thread_t *) svc_args[0],
          (RTOS_stack_t *) svc_args[1],
          (uint32_t) svc_args[2],
          (void *) svc_args[3]);
    break;

    case 2:
//      RTOS_mutexCreate((RTOS_mutex_t *) svc_args[0], (uint32_t) svc_args[1]);
    break;

    case 3:
//      returnStatus = RTOS_mutexLock((RTOS_mutex_t *) svc_args[0],
//          (uint32_t) svc_args[1]);
    break;

    case 4:
//      RTOS_mutexRelease((RTOS_mutex_t *) svc_args[0]);
    break;

    case 5:
//      RTOS_semaphoreCreate((RTOS_semaphore_t *) svc_args[0],
//          (uint32_t) svc_args[1]);
    break;

    case 6:
//      returnStatus = RTOS_semaphoreTake((RTOS_semaphore_t *) svc_args[0],
//          (uint32_t) svc_args[1]);
    break;

    case 7:
//      RTOS_semaphoreGive((RTOS_semaphore_t *) svc_args[0]);
    break;

    case 8:
//      RTOS_mailboxCreate((RTOS_mailbox_t *) svc_args[0], (void *) svc_args[1],
//          (uint32_t) svc_args[2], (uint32_t) svc_args[3]);
    break;

    case 9:
//      returnStatus = RTOS_mailboxWrite((RTOS_mailbox_t *) svc_args[0],
//          (uint32_t) svc_args[1], (const void * const) svc_args[2]);
    break;

    case 10:
//      returnStatus = RTOS_mailboxRead((RTOS_mailbox_t *) svc_args[0],
//          (uint32_t) svc_args[1], (void * const) svc_args[2]);
    break;

    default:
      /* Not supported svc call */
      ASSERT(0);
    break;
  }

  /* Check svc number for return status */
  switch(svc_number)
  {

    case 3:
    case 6:
    case 9:
    case 10:
      /* Check return status */
      if(2 == returnStatus)
      {
        /* Context switch was triggered, update program counter,
         * when the context is restored the thread will try again */
        svc_args[6] = svc_args[6] - 2;
      }
      else
      {
        /* No context switch was triggered, pass return value */
        svc_args[0] = returnStatus;
      }
    break;

    default:
      /* Handled above */
    break;
  }
}

/**
 * @brief   SysTick Handler
 * @note
 * @param   None
 * @retval  None
 */
void RTOS_SysTick_Handler(void)
{
  /* Trigger context switch, set PendSV to pending */
  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

  /* Increment SysTick counter */
  ++sysTickCounter;
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
