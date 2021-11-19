/*******************************************************************************
 * @file    rtos_semaphore.h
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    27 Jul 2019
 *
 * @brief   RTOS Semaphore
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
#ifndef __INC_RTOS_SEMAPHORE_H_
#define __INC_RTOS_SEMAPHORE_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @addtogroup rtos_semaphore
 * @{
 */

/**
 * @defgroup rtos_semaphore_exported_typedefs
 * @{
 */

/**
 * @brief      Semaphore type
 * @note
 * @see
 */
typedef struct {
	uint32_t semaphoreValue; /**< Semaphore counter value */
	RTOS_list_t waitingList; /**< Waiting list of the semaphore */
} RTOS_semaphore_t;

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_functions
 * @{
 */

void RTOS_semaphoreCreate(RTOS_semaphore_t *pSemaphore, uint32_t initialValue);
void RTOS_SVC_semaphoreCreate(RTOS_semaphore_t *pSemaphore,
		uint32_t initialValue);

uint32_t RTOS_semaphoreTake(RTOS_semaphore_t *pSemaphore, int32_t waitTime);
uint32_t RTOS_SVC_semaphoreTake(RTOS_semaphore_t *pSemaphore, int32_t waitTime);

void RTOS_semaphoreGive(RTOS_semaphore_t *pSemaphore);
void RTOS_SVC_semaphoreGive(RTOS_semaphore_t *pSemaphore);

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

#endif /*__INC_RTOS_SEMAPHORE_H_ */
