/* USER CODE BEGIN Header */
/**
  *  *  Created on: Feb 10, 2022
  *      Author: Hazem
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "gp_driver.h"
#include "rockblock.h"

/* Private variables ---------------------------------------------------------*/
osThreadId Task1Handle;
osThreadId Task2Handle;
osSemaphoreId Binary_SemHandle;
osStaticSemaphoreDef_t Binary_SemControlBlock;
osSemaphoreId UART_Binary_SEMHandle;
osStaticSemaphoreDef_t UART_Binary_SEMControlBlock;

char Uart_1_msg[250];
unsigned short Uart_1_mgr[7]={0,0,0,0,'\n',0,0};

/*
 * UART Manager
 * 0- count
 * 1- signal
 * 2- Bridge
 * 3- Terminator should 1: Terminator / 0:Interrupt
 * 4- Terminator char
 * 5- time constant
 * 6- time counter
 */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

void Task1_App(void const * argument);
void Task2_App(void const * argument);

int main(void)
{
  /* USER CODE BEGIN Init */
  init_GP(PA,0,IN,I_PP);

  /*NOTICE Here >D*/
  //this part can be refactored to be enabled for a certain EXTI with other Ports
  //ther is an issue FreeRtos has with interrupts in which we need to change the groub prioirity of each used interrupt as
  //ARM assignes it by default to 0 and FreeRtos checks that there is no maskable interrupt have priority higher than Systick which
  //is configurable with FreeRTOSConfig.h file but because we have no time i disabled this check in free rtos :D

  __disable_irq();
  // map the pin to EXTI peripheral
  AFIO->EXTICR[0] = 0x00; // map port A to EXTI periheral
  //enable the interrupt activity
  EXTI->IMR |=1; //not maskable interrupt enabled
  EXTI->RTSR |= 1;//interrupt occurs on rising trigger
  NVIC_EnableIRQ(EXTI0_IRQn);//enable EXTI0 for NVIC peripheral which connects interrupt signal from exti peripheral
  __enable_irq();//enable processor main interrupt flag

  init_GP(PC,14,OUT50, O_GP_PP);
  init_GP(PC,13,OUT50, O_GP_PP);

  UART_Init(Uart1,9600);
  UART_Tx_Stream(Uart1, "H");//flushing char
  UART_Tx_Stream(Uart1, "Hellow from UART 1\n");

  /* Create the semaphores(s) */
  /* definition and creation of Binary_Sem */
  osSemaphoreStaticDef(Binary_Sem, &Binary_SemControlBlock);
  Binary_SemHandle = osSemaphoreCreate(osSemaphore(Binary_Sem), 1);

  /* definition and creation of UART_Binary_SEM */
  osSemaphoreStaticDef(UART_Binary_SEM, &UART_Binary_SEMControlBlock);
  UART_Binary_SEMHandle = osSemaphoreCreate(osSemaphore(UART_Binary_SEM), 1);

  /* add semaphores initial status, ... */
  osSemaphoreRelease(UART_Binary_SEMHandle);

  /* Create the thread(s) */
  /* definition and creation of Task1 */
  osThreadDef(Task1, Task1_App, osPriorityNormal, 0, 128);
  Task1Handle = osThreadCreate(osThread(Task1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, Task2_App, osPriorityAboveNormal, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* Start scheduler */
  osKernelStart();

  /* Infinite loop */
  while (1)
  {

  }
}

/* START INTERRUPT HANDLERS */
void USART1_IRQHandler(){
	UART_ISR(Uart1, Uart_1_mgr, Uart_1_msg);//receive UART Data Asynchronously with interrupt
}

void EXTI0_IRQHandler(){
	EXTI->PR |=1;
	osSemaphoreRelease(UART_Binary_SEMHandle);//release uart to enable higher priority task to run
	osSemaphoreRelease(Binary_SemHandle);
}
/* END INTERRUPT HANDLERS */

/**
  * @brief  Function implementing the Task1 thread.
  * @param  argument: Not used
  * @retval None
  */
void Task1_App(void const * argument)
{
  /* Infinite loop */
	for(;;)
	{
		/* Check modem communication */
		osSemaphoreWait(UART_Binary_SEMHandle, osWaitForever);
		Receive_from_Rock_Modem(Uart_1_mgr,Uart_1_msg);
		osSemaphoreRelease(UART_Binary_SEMHandle);
		/* Receive response in UART_1_msg*/

		if (strstr(Uart_1_msg, "TURNOFF") != NULL) {
			W_GP(PC,14,LOW);
		}
		else if (strstr(Uart_1_msg, "TURNON") != NULL) {
			W_GP(PC,14,HIGH);
		}
		//clear received buffer
		str_empty(Uart_1_msg);
		Uart_1_mgr[0] = 0;

		osDelay(500);
	}
}

/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
void Task2_App(void const * argument)
{
  /* Infinite loop */
	for(;;)
	{
		osSemaphoreWait(Binary_SemHandle, osWaitForever);

		osSemaphoreWait(UART_Binary_SEMHandle, osWaitForever);
		Send_To_Rock_Modem(Uart_1_mgr,Uart_1_msg,"ALERT!");
		osSemaphoreRelease(UART_Binary_SEMHandle);
		osDelay(500);
	}
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

