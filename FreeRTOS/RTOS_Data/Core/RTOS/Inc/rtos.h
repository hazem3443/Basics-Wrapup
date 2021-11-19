/*******************************************************************************
 * @file    rtos.h
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

/* Define to prevent recursive inclusion */
#ifndef __INC_RTOS_H_
#define __INC_RTOS_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stddef.h>
#include <string.h>

#include "stm32f1xx.h"
//#include "stm32f4xx.h"

#include "rtos_config.h"

#include "rtos_list.h"
#include "rtos_thread.h"

#include "rtos_mutex.h"
#include "rtos_semaphore.h"
#include "rtos_mailbox.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @defgroup rtos_exported_typedefs
 * @{
 */

/**
 * @brief   RTOS return types
 */
typedef enum
{
  RTOS_SUCCESS,
  RTOS_FAILURE,
  RTOS_CONTEXT_SWITCH_TRIGGERED
} RTOS_return_t;

/**
 * @}
 */

/**
 * @defgroup rtos_exported_defines
 * @{
 */

/**
 * @brief   Waiting flags
 */
#define NO_WAIT                 ((int32_t) 0)
#define WAIT_INDEFINITELY       ((int32_t) -1)

/**
 * @}
 */

/**
 * @defgroup rtos_exported_macros
 * @{
 */

/**
 * @brief   Memory word access
 */
#define MEM32_ADDRESS(ADDRESS) (*((volatile unsigned long *)(ADDRESS)))

/**
 * @}
 */

/**
 * @defgroup rtos_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_exported_functions
 * @{
 */

void RTOS_init(void);
void RTOS_schedulerStart(void);
void RTOS_SVC_schedulerStart(void);
void RTOS_SVC_Handler_main(uint32_t * svc_args);
void RTOS_SysTick_Handler(void);
uint32_t RTOS_isSchedulerRunning(void);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /*__INC_RTOS_H_ */
