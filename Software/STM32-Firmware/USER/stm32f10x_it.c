/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.5.0
 * @date    08-April-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "myInclude.h"
#include "Robot.h"

static uint8_t TIM_count;


/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while(1)
	{
	}
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while(1)
	{
	}
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while(1)
	{
	}
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while(1)
	{
	}
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
	if(TimingDelay)
	{
		TimingDelay--;
	}
	SysTime++;
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) )
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void EXTI9_5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line9);
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
	{
		RxBuffer1 = USART_ReceiveData(USART1);


		/*
		 * USART_SendData(USART1,RxBuffer);
		 * while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		 */
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART3, USART_IT_RXNE) == SET)
	{
		RxBuffer3 = USART_ReceiveData(USART3);
	}
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
#ifdef __ENCODER_H
	if(TIM2->CR1 & 0x10)
	{
		ENC1_Base -= 10000;
	}
	else
	{
		ENC1_Base += 10000;
	}
#endif
	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */

void TIM1_UP_IRQHandler(void)
{
	IMU_filter();
	if(FLAG & A_START)
	{
		TIM_count++;

		if(TIM_count % 2)
		{
			if(FLAG & EC_START)
			{
			CTRL_compute_AngleX();
			MOTOR_EC( (int)CTRL_AngleX.Output); 
			}
		}
		else
		{
			CTRL_compute_AngleY();
			MOTOR_A( (int)CTRL_AngleY.Output);
		}

		if(TIM_count == 5)
		{
			if(FLAG & EC_START)
			{
			SpeedX		= (double)get_ENC2_Count() - ENC2_Count_last;
			ENC2_Count_last = get_ENC2_Count();
			CTRL_compute_SpeedX();
			}
		}
		else if(TIM_count == 10)
		{
			SpeedY		= (double)get_ENC1_Count() - ENC1_Count_last; 
			ENC1_Count_last = get_ENC1_Count();
			CTRL_compute_SpeedY(); 
			TIM_count = 0;
			//printf("%d\n",  get_ENC1_Count()); 
		}
	}
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void TIM4_IRQHandler(void)
{
#ifdef __ENCODER_H
	if(TIM4->CR1 & 0x10)
	{
		ENC2_Base -= 10000;
	}
	else
	{
		ENC2_Base += 10000;
	}
#endif
	TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void DMA1_Channel7_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC7) )
	{
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
