/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* Function processing DMA Rx data. Counts how many capital and small letters are in sentence.
 * Result is supposed to be stored in global variable of type "letter_count_" that is defined in "main.h"
 *
 * @param1 - received sign
 */
void proccesDmaData(const uint8_t* data, uint16_t len);


/* Space for your global variables. */



	// type your global variables here:
	int start = 0;
	int count = 0;
	int capL = 0;
	int lowL = 0;



int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();

  /* Space for your local variables, callback registration ...*/


  uint8_t tx_data[1000];
  uint8_t tx_data1[] = "Buffer capacity: ";
  uint8_t tx_data2[] = " bytes, occupied memory: ";

  uint8_t tx_data3[] = " bytes, load [in %]: ";

  uint8_t tx_data4[] = "%\r\n";

  char buffer_size_string[4];
  char used_memory_string[4];
  char load_string[3];
  int buffer_size_int = DMA_USART2_BUFFER_SIZE;
  sprintf(buffer_size_string, "%d", buffer_size_int);


  	  //type your code here:
  USART2_RegisterCallback(proccesDmaData);

  while (1)
  {


	  /* Periodic transmission of information about DMA Rx buffer state.
	   * Transmission frequency - 5Hz.
	   * Message format - "Buffer capacity: %d bytes, occupied memory: %d bytes, load [in %]: %f%"
	   * Example message (what I wish to see in terminal) - Buffer capacity: 1000 bytes, occupied memory: 231 bytes, load [in %]: 23.1%
	   */

  	  	  	  //type your code here:



		sprintf(used_memory_string, "%d", occupied_memory);

		gcvt(load, 4, load_string);

	    USART2_PutBuffer(tx_data1, sizeof(tx_data1));
		LL_mDelay(500);
		USART2_PutBuffer(buffer_size_string, sizeof(buffer_size_string));
		LL_mDelay(500);
		USART2_PutBuffer(tx_data2, sizeof(tx_data2));
		LL_mDelay(500);
		USART2_PutBuffer(used_memory_string, sizeof(used_memory_string));
		LL_mDelay(500);
		USART2_PutBuffer(tx_data3, sizeof(tx_data3));
		LL_mDelay(500);
		USART2_PutBuffer(load_string, sizeof(load_string));
		LL_mDelay(500);
		USART2_PutBuffer(tx_data4, sizeof(tx_data4));
		LL_mDelay(500);



  }
  /* USER CODE END 3 */
}


void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
}

/*
 * Implementation of function processing data received via USART.
 */
void proccesDmaData(const uint8_t* data, uint16_t len)
{
	/* Process received data */

		// type your algorithm here:

	for(uint8_t i = 0; i < len; i++)
	{
		if(*(data+i) == '#')
		{
			start = 1;
		}
		else if(*(data+i) == '$')
		{
			start = 0;
			count = 0;
			lowL = 0;
		    capL = 0;
		}

		if(start == 1)
		{
			count++;
			if(count >= 34)
			{
				start = 0;
				count = 0;
				lowL = 0;
				capL = 0;
			}
			else
			{
				if(*(data+i) > 96 && *(data+i) < 123)
				{
					lowL++;
				}
				if(*(data+i) > 64 && *(data+i) < 91)
				{
					capL++;
				}
			}

		}


	}
}


void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(char *file, uint32_t line)
{ 

}

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
