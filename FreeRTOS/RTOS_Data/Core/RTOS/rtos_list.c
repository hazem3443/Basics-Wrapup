/*******************************************************************************
 * @file    rtos_list.c
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

/* Includes */
#include "Inc/rtos.h"

/**
 * @addtogroup rtos
 * @{
 */

/**
 * @defgroup rtos_list
 * @brief
 * @{
 */

/**
 * @defgroup rtos_list_private_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_private_defines
 * @{
 */

/**
 * @}
 */
#define LIST_END_ITEM_VALUE                     ((uint32_t) 0xFFFFFFFFu)
/**
 * @defgroup rtos_list_private_macros
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_private_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_private_variables
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_private_function_prototypes
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_private_functions
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_list_exported_functions
 * @{
 */

/**
 * @brief   Initialize thread list
 * @note
 * @param   RTOS_list_t *
 * @retval  None
 */
void RTOS_listInit(RTOS_list_t * pList)
{
  /* Check input parameters */
  ASSERT(NULL != pList);

  /* Currently no threads in the list, so the index pointing to the end */
  pList->pIndex = (RTOS_listItem_t *) &pList->listEnd;

  /* List is empty, so the end pointing to itself */
  pList->listEnd.pNext = (RTOS_listItem_t *) &pList->listEnd;
  pList->listEnd.pPrev = (RTOS_listItem_t *) &pList->listEnd;

  /* Set item value for the list end */
  pList->listEnd.itemValue = LIST_END_ITEM_VALUE;

  /* Number of threads in the list is zero */
  pList->numOfItems = 0;
}

/**
 * @brief   Insert thread item at the end into a list
 * @note
 * @param   RTOS_list_t *, RTOS_listItem_t *
 * @retval  None
 */
void RTOS_listInsertEnd(RTOS_list_t * pList, RTOS_listItem_t * pNewItem)
{
  /* Check input parameters */
  ASSERT(NULL != pList);
  ASSERT(NULL != pNewItem);

  /* Next of the new item is the next of the current item */
  pNewItem->pNext = pList->pIndex->pNext;

  /* Previous of the new item is the current item */
  pNewItem->pPrev = pList->pIndex;

  /* Change the item pointing to the current item as previous,
   * it shall point now to the new item */
  pList->pIndex->pNext->pPrev = pNewItem;

  /* Current item shall point to the new item as next */
  pList->pIndex->pNext = pNewItem;

  /* Make the index points to the new item */
  pList->pIndex = pNewItem;

  /* Set the list container for the new item */
  pNewItem->pList = (void *) pList;

  /* Increment number of items in the list */
  pList->numOfItems++;
}

/**
 * @brief   Insert thread item by priority order
 * @note
 * @param   RTOS_list_t *, RTOS_listItem_t *
 * @retval  None
 */
void RTOS_listInsert(RTOS_list_t * pList, RTOS_listItem_t * pNewItem)
{
  /* Check input parameters */
  ASSERT(NULL != pList);
  ASSERT(NULL != pNewItem);

  /* Temp for the insert index */
  RTOS_listItem_t * pInsertIndex = (RTOS_listItem_t *) &pList->listEnd;

  /* Get insert index, find the high item value */
  while((pInsertIndex->pNext != (RTOS_listItem_t *) &pList->listEnd)
      && (pInsertIndex->pNext->itemValue <= pNewItem->itemValue))
  {
    pInsertIndex = pInsertIndex->pNext;
  }

  /* Connect the new item with insert index */
  pNewItem->pNext = pInsertIndex->pNext;
  pNewItem->pPrev = pInsertIndex;
  pInsertIndex->pNext->pPrev = pNewItem;
  pInsertIndex->pNext = pNewItem;

  /* Set the list container for the new item */
  pNewItem->pList = (void *) pList;

  /* Increment number of items in the list */
  pList->numOfItems++;
}

/**
 * @brief   Remove thread item from a list
 * @note
 * @param   RTOS_listItem_t *
 * @retval  None
 */
void RTOS_listRemove(RTOS_listItem_t * pRemovedItem)
{
  /* Check input parameters */
  ASSERT(NULL != pRemovedItem);

  /* Previous of the next item will be the previous of the removed item */
  pRemovedItem->pNext->pPrev = pRemovedItem->pPrev;

  /* Next of the previous item will the next of the removed item */
  pRemovedItem->pPrev->pNext = pRemovedItem->pNext;

  /* Temp list pointer */
  RTOS_list_t * pList;

  /* Get list of the removed item */
  pList = (RTOS_list_t *) pRemovedItem->pList;

  /* If the index pointing to the removed item,
   * make it points the previous item */
  if(pRemovedItem == pList->pIndex)
  {
    pList->pIndex = pRemovedItem->pPrev;
  }
  else
  {
    /* Index pointing somewhere else */
  }

  /* Remove item from the list */
  pRemovedItem->pList = NULL;
  if(NULL != pList)
  pList->numOfItems--;

  /* Decrement number of thread items in the list */
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
