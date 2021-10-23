/*******************************************************************************
 * @file    rtos_list.h
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    15 Jul 2019
 *
 * @brief   RTOS List
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
#ifndef __RTOS_LIST_H_
#define __RTOS_LIST_H_

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
 * @addtogroup rtos_list
 * @{
 */

/**
 * @defgroup rtos_list_exported_typedefs
 * @{
 */

/**
 * @brief      Linked list item type
 * @note
 * @see
 */
struct listItem_t
{
  uint32_t itemValue;            /**< Item value used for sorting in non ready lists */
  struct listItem_t * pNext;     /**< Pointer to the next list item */
  struct listItem_t * pPrev;     /**< Pointer to the previous list item */
  void * pThread;                /**< Pointer to the thread of the item */
  void * pList;                  /**< Pointer to the list in which the item it */
};
typedef struct listItem_t RTOS_listItem_t;

/**
 * @brief      Linked list item type
 * @note
 * @see
 */
typedef struct
{
  uint32_t itemValue;          /**< Item value used for sorting in non ready lists */
  RTOS_listItem_t * pNext;     /**< Pointer to the next list item */
  RTOS_listItem_t * pPrev;     /**< Pointer to the previous list item */
} RTOS_listEnd_t;


/**
 * @brief      Linked list type
 * @note
 * @see
 */
typedef struct
{
  uint32_t numOfItems;           /**< Number of threads items in the list */
  RTOS_listItem_t * pIndex;        /**< Pointer to the current item */
  RTOS_listEnd_t listEnd;          /**< List end */
} RTOS_list_t;

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_defines
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_functions
 * @{
 */

void RTOS_listInit(RTOS_list_t * pList);
void RTOS_listInsertEnd(RTOS_list_t * pList, RTOS_listItem_t * pItem);
void RTOS_listInsert(RTOS_list_t * pList, RTOS_listItem_t * pNewItem);
void RTOS_listRemove(RTOS_listItem_t * pItem);

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

#endif /*__RTOS_LIST_H_ */
