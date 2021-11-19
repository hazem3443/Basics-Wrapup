/*******************************************************************************
 * @file    rtos_mutex.c
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

/* Includes */
#include "Inc/rtos.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup rtos_mutex
 * @brief
 * @{
 */

/**
 * @defgroup rtos_mutex_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mutex_exported_functions
 * @{
 */

/**
 * @brief   Mutex create
 * @note
 * @param   RTOS_mutex_t *
 * @retval  None
 */
void RTOS_mutexCreate(RTOS_mutex_t *pMutex, uint32_t initialValue) {
	/* Check input parameters */
	ASSERT(NULL != pMutex);
	ASSERT((initialValue == 0) || (initialValue == 1));

	/* Initialize mutex waiting list */
	RTOS_listInit(&pMutex->waitingList);

	/* Initialize mutex value */
	pMutex->mutexValue = initialValue;
}

/**
 * @brief   Mutex lock
 * @note
 * @param   RTOS_mutex_t *, uint32_t
 * @retval  uint32_t
 * ret = 1 means locked successfully
 *  2 means already locked by another thread move the current thread from ready list to waiting list and switch to the next thread
 */
uint32_t RTOS_mutexLock(RTOS_mutex_t *pMutex, int32_t waitTime) {
	/* Check input parameters */
	ASSERT(NULL != pMutex);
	ASSERT(WAIT_INDEFINITELY <= waitTime);

	/* Mutex lock return status */
	RTOS_return_t returnStatus = RTOS_FAILURE;

	/* Pointer to the current running thread */
	RTOS_thread_t *pRunningThread;

	/* Variable to terminate the while loop */
	uint32_t terminate = 0;

	/* Try to lock the mutex */
	while (1 != terminate) {
		/* Check mutex value, note in ARMv7-M exceptions automatically clear the
		 * exclusive state in the local monitor, no need to use CLREX instruction */
		if (1 == __LDREXW(&pMutex->mutexValue)) //if ==0 means another thread already take this mutex
				{
			/* Mutex is free, locked it */
			if (0 == __STREXW(0, &pMutex->mutexValue)) {
				/* Required before accessing protected resource */
				__DMB();

				/* Mutex is locked */
				returnStatus = RTOS_SUCCESS;

				/* Mutex lock succeeded, terminate the loop */
				terminate = 1;
			} else {
				/* Mutex can not be locked, do nothing */
			}
		} else {
			/* Mutex is locked, terminate the loop */
			terminate = 1;
		}
	}

	/* Check waiting flag and return status */
	/*if another thread takes this mutex then we need to remove this from ready list
	 * and context switch to another thread till that thread release the mutex
	 */
	if ((NO_WAIT != waitTime) && (RTOS_SUCCESS != returnStatus)) {
		/* Get current running thread */
		pRunningThread = RTOS_threadGetRunning();

		/* Remove current thread from ready list */
		RTOS_listRemove(&pRunningThread->genericListItem);

		/* Put current thread into the waiting list in order of itemvalue as ordering parameter instead of priority*/
		RTOS_listInsert(&pMutex->waitingList, &pRunningThread->eventListItem);

		/* Trigger context switch, set PendSV to pending */
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

		/* Check waiting time */
		if (NO_WAIT < waitTime) {
			/* Waiting time configured, add current to the timer list */
			RTOS_threadAddRunningToTimerList((uint32_t)waitTime);
		} else {
			/* Thread will wait indefinitely, do nothing */
		}

		/* Return to SVC as indication of context switching */
		returnStatus = RTOS_CONTEXT_SWITCH_TRIGGERED;
	} else {
		/* No blocking required, do nothing */
	}

	/* Return */
	return returnStatus;
}

/**
 * @brief   Mutex release
 * @note
 * @param   RTOS_mutex_t *
 * @retval  None
 *
 * make the mutex value by 1 and move first thread in the waiting list to ready list which contains (svc_args[6] - 2)
 * or will return to svc 3 trying to lock the mutex and move on
 */
void RTOS_mutexRelease(RTOS_mutex_t *pMutex) {
	/* Check input parameters */
	ASSERT(NULL != pMutex);

	/* Pointer to the unblocked thread */
	RTOS_thread_t *pThread;

	/* Required before releasing protected resource */
	__DMB();

	/* Release the mutex */
	pMutex->mutexValue = 1;

	/* Get highest priority waiting thread, the one next from the end */
	if (0 < pMutex->waitingList.numOfItems) {
		pThread = pMutex->waitingList.listEnd.pNext->pThread;

		/* Check returned thread */
		ASSERT(NULL != pThread);

		/* Remove the returned thread item from the waiting list */
		RTOS_listRemove(&pThread->eventListItem);

		/* Check if the generic item in any list */
		if (NULL != pThread->genericListItem.pList) {
			/* Remove the generic item from the current list,
			 * as it will be inserted into ready list */
			RTOS_listRemove(&pThread->genericListItem);
		} else {
			/* Do nothing, generic item is not in any list */
		}

		/* Add the returned thread into ready list */
		RTOS_threadAddToReadyList(pThread);
	} else {
		/* No threads are waiting, do nothing */
	}
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
