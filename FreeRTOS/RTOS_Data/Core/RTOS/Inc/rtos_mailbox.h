/*******************************************************************************
 * @file    rtos_mailbox.h
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

/* Define to prevent recursive inclusion */
#ifndef __INC_RTOS_MAILBOX_H_
#define __INC_RTOS_MAILBOX_H_

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
 * @addtogroup rtos_mailbox
 * @{
 */

/**
 * @defgroup rtos_mailbox_exported_typedefs
 * @{
 */

/**
 * @brief      Mailbox type
 * @note
 * @see
 */
typedef struct {
	int8_t *pStart; /**< Start location */
	int8_t *pEnd; /**< Last location */
	int8_t *pReadIndex; /**< Read location */
	int8_t *pWriteIndex; /**< Write location */
	uint32_t bufferLength; /**< Length of the mailbox buffer */
	uint32_t messageSize; /**< Mailbox message size in bytes */
	uint32_t messagesNum; /**< Current number of messages inside the buffer */
	RTOS_list_t waitingList; /**< Waiting list */
} RTOS_mailbox_t;

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_mailbox_exported_functions
 * @{
 */

void RTOS_mailboxCreate(RTOS_mailbox_t *pMailbox, void *pBuffer,
		uint32_t bufferLength, uint32_t messageSize);
void RTOS_SVC_mailboxCreate(RTOS_mailbox_t *pMailbox, void *pBuffer,
		uint32_t bufferLength, uint32_t messageSize);

uint32_t RTOS_mailboxWrite(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		const void *const pMessage);
uint32_t RTOS_SVC_mailboxWrite(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		const void *const pMessage);

uint32_t RTOS_mailboxRead(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		void *const pMessage);
uint32_t RTOS_SVC_mailboxRead(RTOS_mailbox_t *pMailbox, int32_t waitTime,
		void *const pMessage);

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

#endif /*__INC_RTOS_MAILBOX_H_ */
