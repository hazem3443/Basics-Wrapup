#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "UART.h"

#include "../RTOS/Inc/rtos.h"

static RTOS_thread_t thread1;
static RTOS_stack_t thread1stack;
static RTOS_thread_t thread2;
static RTOS_stack_t thread2stack;

static RTOS_mutex_t mutex1;

void thread1function(void)
{
	init_GP(PC, 13, OUT50, O_GP_PP);
	while(1)
	{
		toggle_GP(PC, 13);

		for (int var = 0; var < 10000; ++var)
		{
		}
	}
}
/**
 * @brief   thread2function
 * @note
 * @param   none
 * @retval  none
 */
void thread2function(void)
{
	init_GP(PC, 14, OUT50, O_GP_PP);
	while(1)
	{
		toggle_GP(PC, 14);

		for (int var = 0; var < 100000; ++var)
		{
		}
	}
}

int main (void)
{
	/*
	//	SysTick_Config(SystemCoreClock / 1000);
//	Systic_init();
////	init_GP(PC, 13, OUT50, O_GP_PP);
//	while(1)
//	{
////		toggle_GP(PC, 13);
////		DelayMs(1000);
//	}
*/
	RTOS_init();

	//this function will push those args to registers R0 to R3 respectively
	RTOS_SVC_threadCreate(&thread1, &thread1stack, 1, thread1function);
	RTOS_SVC_threadCreate(&thread2, &thread2stack, 1, thread2function);

	RTOS_SVC_mutexCreate(&mutex1, 1);

	RTOS_SVC_schedulerStart();

	/* Infinite loop */
	while(1)
	{
	}
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
