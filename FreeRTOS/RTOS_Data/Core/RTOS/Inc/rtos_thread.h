/*******************************************************************************
 * @file    rtos_thread.h
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

/* Define to prevent recursive inclusion */
#ifndef __RTOS_THREAD_H_
#define __RTOS_THREAD_H_

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @addtogroup rtos_thread
 * @{
 */

/**
 * @defgroup rtos_thread_exported_typedefs
 * @{
 */

/**
 * @brief      Thread type
 * @note
 * @see
 */
typedef struct thread_t {
	uint32_t pStackPointer; /**< Stack pointer */
	uint32_t priority; /**< Thread priority */
	uint32_t threadID; /**< Used for trace */
	RTOS_listItem_t genericListItem; /**< Generic list item of this thread */
	RTOS_listItem_t eventListItem; /**< Event list item of this thread */
} RTOS_thread_t;

/**
 * @brief      Thread stack type
 * @note
 * @see
 */
typedef struct {
	uint64_t stack[THREAD_STACK_SIZE]; /**< Thread stack */
} RTOS_stack_t;

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_thread_exported_functions
 * @{
 */

void RTOS_threadCreate(RTOS_thread_t *pThread, RTOS_stack_t *pStack,
		uint32_t priority, void *pFunction);
void RTOS_SVC_threadCreate(RTOS_thread_t *pThread, RTOS_stack_t *pStack,
		uint32_t priority, void *pFunction);

void RTOS_threadInitLists(void);
RTOS_thread_t* RTOS_threadGetRunning(void);
void RTOS_threadSwitchRunning(void);
void RTOS_threadAddToReadyList(RTOS_thread_t *pThread);

void RTOS_threadRefreshTimerList(void);
void RTOS_threadAddRunningToTimerList(uint32_t waitTime);

void RTOS_SVC_threadDelay(uint32_t waitTime);

void RTOS_threadDestroy(RTOS_thread_t *pThread);
void RTOS_SVC_threadDestroy(RTOS_thread_t *pThread);

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

#endif /*__RTOS_THREAD_H_ */
