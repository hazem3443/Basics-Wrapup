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

/**
 * @brief   Currently running thread pointer.
 */
extern RTOS_thread_t * pRunningThread;

/**
 * @}
 */

/**
 * @defgroup rtos_private_function_prototypes
 * @{
 */

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

}

/**
 * @brief   SVC handler main
 * @note
 * @param   uint32_t *
 * @retval  None
 */
void RTOS_SVC_Handler_main(uint32_t * svc_args)
{
  uint8_t svc_number;

  /* Memory[(Stacked PC)-2] */
  svc_number = ((char *) svc_args[6])[-2];

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

    default:
      /* Not supported svc call */
      ASSERT(0);
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
