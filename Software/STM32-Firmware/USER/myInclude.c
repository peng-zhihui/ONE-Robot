#include "myInclude.h"

/**************************time***************************/
__IO uint32_t SysTime, TimingDelay;

void SysTick_Init(void)
{
	if(SysTick_Config(SystemCoreClock / SYS_DIV) )
	{
		while(1)
		{
			;
		}
	}
}

void delay(__IO uint32_t nTime)
{
	TimingDelay = (uint32_t)(nTime * SYS_DELAY);
	while(TimingDelay)
	{
		;
	}
}

uint32_t millis(void)
{
	return( (uint32_t)(SysTime / SYS_DELAY) );
}

uint32_t micros(void)
{
	return( (uint32_t)(SysTime * SYS_PERIOD) );
}


/**************************serial***************************/
uint8_t RxBuffer1,RxBuffer3;

void USART1_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate		= 115200;
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;
	USART_InitStructure.USART_Parity		= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel			= USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 10;
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART1->SR;
}

void USART3_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate		= 115200;
	USART_InitStructure.USART_WordLength		= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits		= USART_StopBits_1;
	USART_InitStructure.USART_Parity		= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode			= USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStructure.NVIC_IRQChannel			= USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		= 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 7;
	NVIC_InitStructure.NVIC_IRQChannelCmd			= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART3->SR;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{
		;
	}
	return(ch);
}

/**************************i2c***************************/

/**************************gpio***************************/
void pinMode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode	= Mode;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;

	if(GPIOx == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void digitalWrite(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Level LEVEL)
{
	switch(LEVEL)
	{
		case LOW:
			GPIOx->BRR |= GPIO_Pin;
			break;
		case HIGH:
			GPIOx->BSRR |= GPIO_Pin;
			break;
		case TURN:
			GPIOx->ODR ^= GPIO_Pin;
			break;
	}
}

uint8_t digitalRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) );
}

