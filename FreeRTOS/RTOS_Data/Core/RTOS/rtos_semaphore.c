/*******************************************************************************
 * @file    rtos_semaphore.c
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

/* Includes */
#include "Inc/rtos.h"

/**
 * @addtogroup stm32_examples
 * @{
 */

/**
 * @defgroup rtos_semaphore
 * @brief
 * @{
 */

/**
 * @defgroup rtos_semaphore_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_semaphore_exported_functions
 * @{
 */

/**
 * @brief   Semaphore create
 * @note
 * @param   RTOS_semaphore_t *
 * @retval  None
 */
void RTOS_semaphoreCreate(RTOS_semaphore_t *pSemaphore, uint32_t initialValue) {
	/* Check input parameters */
	ASSERT(NULL != pSemaphore);

	/* Initialize semaphore waiting list */
	RTOS_listInit(&pSemaphore->waitingList);

	/* Initialize semaphore value */
	pSemaphore->semaphoreValue = initialValue;
}

/**
 * @brief   Semaphore take
 * @note
 * @param   RTOS_semaphore_t *, uint32_t
 * @retval  uint32_t
 */
uint32_t RTOS_semaphoreTake(RTOS_semaphore_t *pSemaphore, int32_t waitTime) {
	/* Check input parameters */
	ASSERT(NULL != pSemaphore);
	ASSERT(WAIT_INDEFINITELY <= waitTime);

	/* Semaphore take return status */
	RTOS_return_t returnStatus = RTOS_FAILURE;

	/* Pointer to the current running thread */
	RTOS_thread_t *pRunningThread;

	/* Temp variable to store the semaphore value */
	uint32_t semaphoreValueTemp = 0;

	/* Variable to terminate the while loop */
	uint32_t terminate = 0;

	/* Try to decrement the semaphore */
	while (1 != terminate) {
		/* Read the semaphore counter value */
		semaphoreValueTemp = __LDREXW(&pSemaphore->semaphoreValue);

		/* Check semaphore counter value, note in ARMv7-M exceptions automatically
		 * clear the exclusive state in the local monitor,
		 * no need to use CLREX instruction */
		if (0 < semaphoreValueTemp) {
			/* Semaphore is not fully taken, take one by decrement */
			if (0
					== __STREXW((semaphoreValueTemp - 1),
							&pSemaphore->semaphoreValue)) {
				/* Required before accessing protected resource */
				__DMB();

				/* Semaphore is taken, return OK */
				returnStatus = RTOS_SUCCESS;

				/* Store succeeded, terminate the loop */
				terminate = 1;
			} else {
				/* Problem during decrementing, try again */
			}
		} else {
			/* Semaphore is not available, terminate the loop */
			terminate = 1;
		}
	}

	/* Check waiting flag and return status */
	if ((NO_WAIT == waitTime) && (RTOS_SUCCESS != returnStatus)) {
		/* Get current running thread */
		pRunningThread = RTOS_threadGetRunning();

		/* Remove current thread from ready list */
		RTOS_listRemove(&pRunningThread->genericListItem);

		/* Put current thread into the waiting list */
		RTOS_listInsert(&pSemaphore->waitingList,
				&pRunningThread->eventListItem);

		/* Trigger context switch, set PendSV to pending */
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

		/* Check waiting time */
		if (NO_WAIT < waitTime) {
			/* Waiting time configured, add current to the timer list */
			RTOS_threadAddRunningToTimerList((uint32_t)waitTime);
		} else {
			/* Thread will wait indefinitely, do nothing */
		}

		/* Return to SVC as indication of context switch */
		returnStatus = RTOS_CONTEXT_SWITCH_TRIGGERED;
	} else {
		/* No blocking required, do nothing */
	}

	/* Return */
	return returnStatus;
}

/**
 * @brief   Semaphore give
 * @note
 * @param   RTOS_semaphore_t *
 * @retval  None
 */
void RTOS_semaphoreGive(RTOS_semaphore_t *pSemaphore) {
	/* Check input parameters */
	ASSERT(NULL != pSemaphore);

	/* Pointer to the unblocked thread */
	RTOS_thread_t *pThread;

	/* Temp variable used to read the semaphore counter value */
	uint32_t semaphoreValueTemp = 0;

	/* Variable to terminate the while loop */
	uint32_t terminate = 0;

	/* Try incrementing the semaphore counter */
	while (1 != terminate) {
		/* Get the semaphore value */
		semaphoreValueTemp = __LDREXW(&pSemaphore->semaphoreValue);

		/* Increment temp variable */
		semaphoreValueTemp++;

		/* Try to store the incremented semaphore value */
		if (0 == __STREXW(semaphoreValueTemp, &pSemaphore->semaphoreValue)) {
			/* Store succeeded, terminate the loop */
			terminate = 1;

			/* Required before releasing protected resource */
			__DMB();
		} else {
			/* Store failed, try again */
		}
	}

	/* Get highest priority waiting thread, the one next from the end */
	if (0 < pSemaphore->waitingList.numOfItems) {
		pThread = pSemaphore->waitingList.listEnd.pNext->pThread;

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
