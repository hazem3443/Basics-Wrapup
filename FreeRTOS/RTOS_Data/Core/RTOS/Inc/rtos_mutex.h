/*******************************************************************************
 * @file    rtos_mutex.h
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    21 Jul 2019
 *
 * @brief   RTOS Mutex
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
#ifndef __INC_RTOS_MUTEX_H_
#define __INC_RTOS_MUTEX_H_

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
 * @addtogroup rtos_mutex
 * @{
 */

/**
 * @defgroup rtos_mutex_exported_typedefs
 * @{
 */

/**
 * @brief      Mutex type
 * @note
 * @see
 */
typedef struct {
	uint32_t mutexValue; /**< Mutex value */
	RTOS_list_t waitingList; /**< Waiting list of the mutex */
} RTOS_mutex_t;

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_functions
 * @{
 */

void RTOS_mutexCreate(RTOS_mutex_t *pMutex, uint32_t initialValue);
void RTOS_SVC_mutexCreate(RTOS_mutex_t *pMutex, uint32_t initialValue);

uint32_t RTOS_mutexLock(RTOS_mutex_t *pMutex, int32_t waitTime);
uint32_t RTOS_SVC_mutexLock(RTOS_mutex_t *pMutex, int32_t waitTime);

void RTOS_mutexRelease(RTOS_mutex_t *pMutex);
void RTOS_SVC_mutexRelease(RTOS_mutex_t *pMutex);

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

#endif /*__INC_RTOS_MUTEX_H_ */
