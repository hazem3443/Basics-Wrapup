#include "stm32f1xx_hal.h"
#include "gp_driver.h"
#include "UART.h"

#include "../RTOS/Inc/rtos.h"

static RTOS_thread_t thread1;
static RTOS_stack_t thread1stack;

static RTOS_thread_t thread2;
static RTOS_stack_t thread2stack;

static RTOS_thread_t thread3;
static RTOS_stack_t thread3stack;

static RTOS_thread_t thread4;
static RTOS_stack_t thread4stack;

static RTOS_mutex_t mutex1;

static RTOS_semaphore_t semaphore1;

static RTOS_mailbox_t mailbox1;
static uint32_t mailbox1buffer[3];

void thread1function(void)
{
	init_GP(PC, 13, OUT50, O_GP_PP);
	W_GP(PC, 13, 1);
	while(1)
	{
		uint32_t msg = 0x11223344;
		RTOS_SVC_mutexLock(&mutex1,-1);
//		RTOS_SVC_semaphoreTake(&semaphore1, 1);

		toggle_GP(PC, 13);
		UART_Tx_Stream(Uart1,"this is task 1\n");
//		RTOS_SVC_semaphoreGive(&semaphore1);

		RTOS_SVC_mutexRelease(&mutex1);

		RTOS_SVC_mailboxWrite(&mailbox1, 10, &msg);

		RTOS_SVC_threadDelay(1000);

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
		uint32_t msg = 0x55667788;
		RTOS_SVC_mutexLock(&mutex1,-1);
//		RTOS_SVC_semaphoreTake(&semaphore1, 1);

		toggle_GP(PC, 14);
		UART_Tx_Stream(Uart1,"this is task 2\n");
//		RTOS_SVC_semaphoreGive(&semaphore1);

		RTOS_SVC_mutexRelease(&mutex1);

		RTOS_SVC_mailboxWrite(&mailbox1, 10, &msg);

		RTOS_SVC_threadDelay(1000);
	}
}

/**
 * @brief   thread3function
 * @note
 * @param   none
 * @retval  none
 */
void thread3function(void)
{
	init_GP(PC, 15, OUT50, O_GP_PP);
	while(1)
	{
		uint32_t msg = 0x99101011;
		RTOS_SVC_mutexLock(&mutex1,-1);
//		RTOS_SVC_semaphoreTake(&semaphore1, 1);

		toggle_GP(PC, 15);
		UART_Tx_Stream(Uart1,"this is task 3\n");
//		RTOS_SVC_semaphoreGive(&semaphore1);

		RTOS_SVC_mutexRelease(&mutex1);

		RTOS_SVC_mailboxWrite(&mailbox1, 10, &msg);

		RTOS_SVC_threadDelay(1000);
	}
}

void thread4function(void)
{
	init_GP(PA, 0, OUT50, O_GP_PP);

	while(1)
	{
		uint32_t msg;
		RTOS_SVC_mutexLock(&mutex1,-1);
//		RTOS_SVC_semaphoreTake(&semaphore1, 1);

		toggle_GP(PA, 0);
		UART_Tx_Stream(Uart1,"this is task 4\n");
//		RTOS_SVC_semaphoreGive(&semaphore1);

		RTOS_SVC_mailboxRead(&mailbox1, 10, &msg);
		if(0x11223344 == msg){
			UART_Tx_Stream(Uart1,"msg from thread 1\n");
		}else if( 0x55667788 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 2\n");
		}
		else if( 0x99101011 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 3\n");
		}else{

		}

		RTOS_SVC_mailboxRead(&mailbox1, 10, &msg);
		if(0x11223344 == msg){
			UART_Tx_Stream(Uart1,"msg from thread 1\n");
		}else if( 0x55667788 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 2\n");
		}
		else if( 0x99101011 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 3\n");
		}else{

		}

		RTOS_SVC_mailboxRead(&mailbox1, 10, &msg);
		if(0x11223344 == msg){
			UART_Tx_Stream(Uart1,"msg from thread 1\n");
		}else if( 0x55667788 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 2\n");
		}
		else if( 0x99101011 ==msg){
			UART_Tx_Stream(Uart1,"msg from thread 3\n");
		}else{

		}

		RTOS_SVC_mutexRelease(&mutex1);

		RTOS_SVC_threadDelay(1000);
	}
}

int main (void)
{
	UART_Init(Uart1,9600);

	UART_Tx_Stream(Uart1,"START\r\n");
	RTOS_init();

	//this function will push those args to registers R0 to R3 respectively
	RTOS_SVC_threadCreate(&thread1, &thread1stack, 1, thread1function);
	RTOS_SVC_threadCreate(&thread2, &thread2stack, 1, thread2function);
	RTOS_SVC_threadCreate(&thread3, &thread3stack, 1, thread3function);
	RTOS_SVC_threadCreate(&thread4, &thread4stack, 0, thread4function);

	RTOS_SVC_mutexCreate(&mutex1, 1);//1 Free, 0 locked by any thread
	RTOS_SVC_semaphoreCreate(&semaphore1, 1);//set semaphore value with 1
	RTOS_SVC_mailboxCreate(&mailbox1, mailbox1buffer, 3, 4);

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
