/*******************************************************************************
 * @file    rtos_mailbox.c
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    28 Jul 2019
 *          
 * @brief   RTOS Mailbox
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
 * @defgroup rtos_mailbox
 * @brief
 * @{
 */

/**
 * @defgroup rtos_mailbox_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_function_prototypes
 * @{
 */

static void checkWaitingThreads(RTOS_mailbox_t *pMailbox);
static void blockCurrentThread(RTOS_mailbox_t *pMailbox);

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_private_functions
 * @{
 */

/**
 * @brief   Check if threads are waiting for a new data
 * @note
 * @param   RTOS_mailbox_t *
 * @retval  None
 */
static void checkWaitingThreads(RTOS_mailbox_t *pMailbox) {
	/* Check input parameters */
	ASSERT(NULL != pMailbox);

	/* Pointer to the unblocked thread */
	RTOS_thread_t *pThread;

	/* Check if threads are waiting for the data */
	if (0 < pMailbox->waitingList.numOfItems) {
		/* Get first one which is ordered by item value in the waiting list */
		pThread = pMailbox->waitingList.listEnd.pNext->pThread;

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
		/* List is empty */
	}
}

/**
 * @brief   Block current thread when buffer is full or empty
 * @note
 * @param   RTOS_mailbox_t *
 * @retval  None
 */
static void blockCurrentThread(RTOS_mailbox_t *pMailbox) {
	/* Pointer to the current running thread */
	RTOS_thread_t *pRunningThread;

	/* Get current running thread */
	pRunningThread = RTOS_threadGetRunning();

	/* Remove current thread from ready list */
	RTOS_listRemove(&pRunningThread->genericListItem);

	/* Put current thread into the waiting list */
	RTOS_listInsert(&pMailbox->waitingList, &pRunningThread->eventListItem);

	/* Trigger context switch, set PendSV to pending */
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_functions
 * @{
 */

/**
 * @brief   Mailbox create
 * @note
 * @param   RTOS_mailbox_t *, void *, uint32_t, uint32_t
 * @retval  None
 */
void RTOS_mailboxCreate(RTOS_mailbox_t *pMailbox, void *pBuffer,
		uint32_t bufferLength, uint32_t messageSize) {
	/* Check input parameters */
	ASSERT(NULL != pMailbox);
	ASSERT(NULL != pBuffer);
	ASSERT(0 != bufferLength);
	ASSERT((1 == messageSize) || (2 == messageSize) || (4 == messageSize));

	/* Set mailbox buffer start and end */
	pMailbox->pStart = (int8_t*) pBuffer;
	pMailbox->pEnd = pMailbox->pStart + (bufferLength * messageSize);

	/* Initialize read and write indices */
	pMailbox->pReadIndex = pMailbox->pStart;
	pMailbox->pWriteIndex = pMailbox->pStart;

	/* Set buffer length and message size */
	pMailbox->bufferLength = bufferLength;
	pMailbox->messageSize = messageSize;

	/* Initialize current number of messages */
	pMailbox->messagesNum = 0;

	/* Initialize mailbox waiting list */
	RTOS_listInit(&pMailbox->waitingList);
}

/**
 * @brief   Mailbox write
 * @note
 * @param   RTOS_mailbox_t *, uint32_t, const void * const
 * @retval  uint32_t
 */
uint32_t RTOS_mailboxWrite(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		const void *const pMessage) {
	/* Check input parameters */
	ASSERT(NULL != pMailbox);
	ASSERT(WAIT_INDEFINITELY <= waitTime);
	ASSERT(NULL != pMessage);

	/* Return status */
	RTOS_return_t returnStatus = RTOS_FAILURE;

	//TODO:we need to make mutex like scope here in order to be able to increase and decrease SVC interrupt priority
	/* here we rely on that SVC interrupt have the highest priority so no one can preempt its operation so no problem for now but for
	 more dynamic operation we need do it execlusively :D
	 */
	/* Check if there is a free place to write */
	if (pMailbox->bufferLength > pMailbox->messagesNum) {
		/* Buffer is not full, copy data */
		memcpy((void*) pMailbox->pWriteIndex, pMessage, pMailbox->messageSize);

		/* Increment write index to point to the next message */
		pMailbox->pWriteIndex += pMailbox->messageSize;

		/* Check if the buffer is written until the end */
		if (pMailbox->pWriteIndex >= pMailbox->pEnd) {
			/* Start over */
			pMailbox->pWriteIndex = pMailbox->pStart;
		} else {
			/* Do nothing, end is still not reached */
		}

		/* Increment current number of messages in the buffer */
		pMailbox->messagesNum++;

		/* Check waiting threads */
		checkWaitingThreads(pMailbox);

		/* New message is added to the buffer, return OK */
		returnStatus = RTOS_SUCCESS;
	} else {
		/* Do nothing, Buffer is full */
	}

	/* Check waiting flag and return status */
	if ((NO_WAIT == waitTime) && (RTOS_SUCCESS != returnStatus)) {
		/* Block current thread or move it to waiting list*/
		blockCurrentThread(pMailbox);

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
 * @brief   Mailbox read
 * @note
 * @param   RTOS_mailbox_t *, uint32_t, void * const
 * @retval  uint32_t
 */
uint32_t RTOS_mailboxRead(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		void *const pMessage) {
	/* Check input parameters */
	ASSERT(NULL != pMailbox);
	ASSERT(WAIT_INDEFINITELY <= waitTime);
	ASSERT(NULL != pMessage);

	/* Return status */
	RTOS_return_t returnStatus = RTOS_FAILURE;

	/* Check if there are messages in the buffer */
	if (0 < pMailbox->messagesNum) {
		/* Buffer is not empty, copy data */
		memcpy(pMessage, (void*) pMailbox->pReadIndex, pMailbox->messageSize);

		/* Increment Read index to point to the next message */
		pMailbox->pReadIndex += pMailbox->messageSize;

		/* Check if the buffer is read until the end */
		if (pMailbox->pReadIndex >= pMailbox->pEnd) {
			/* Start over */
			pMailbox->pReadIndex = pMailbox->pStart;
		} else {
			/* Do nothing, end is still not reached */
		}

		/* Decrement current number of messages in the buffer */
		pMailbox->messagesNum--;

		/* Check waiting threads */
		checkWaitingThreads(pMailbox);

		/* New message is removed from the buffer, return OK */
		returnStatus = RTOS_SUCCESS;
	} else {
		/* Do nothing, Buffer is empty */
	}

	/* Check waiting flag and return status */
	if ((NO_WAIT == waitTime) && (RTOS_SUCCESS != returnStatus)) {
		/* Block current thread */
		blockCurrentThread(pMailbox);

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
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
