/*******************************************************************************
 * @file    rtos_config.h
 * @author  Ahmed Eldeep
 * @email   ahmed@almohandes.org
 * @website http://almohandes.org/stm32
 * @date    15 Jul 2019
 *
 * @brief   RTOS configuration file
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
#ifndef __RTOS_CONFIG_H_
#define __RTOS_CONFIG_H_

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
 * @addtogroup rtos_config
 * @{
 */

/**
 * @defgroup rtos_config_exported_typedefs
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_defines
 * @{
 */

/**
 * @brief   Stack size for each thread in double words. e.g 1024 means 8Kbytes.
 */
#define THREAD_STACK_SIZE                 ((uint32_t) 256u)

/**
 * @brief   Thread maximum priority,
 *          threads can have priority from 0 to (THREAD_MAX_PRIORITY-1)
 */
#define THREAD_PRIORITY_LEVELS               ((uint32_t) 3u)

/**
 * @brief   CPU clock frequency in hertz
 */
#define SYSTEM_CORE_CLOCK_HZ                 ((uint32_t) 8000000u)

/**
 * @brief   System tick frequency in hertz
 */
#define SYS_TICK_RATE_HZ                     ((uint32_t) 1000u)


/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_macros
 * @{
 */

/**
 * @brief   Assert macro
 */
#define ASSERT(x) if((x) == 0) {__disable_irq(); while(1); }

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_constants
 * @{
 */

/**
 * @}
 */

/**
 * @defgroup rtos_config_exported_functions
 * @{
 */

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

#endif /*__RTOS_CONFIG_H_ */
