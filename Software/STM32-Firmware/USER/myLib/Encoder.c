#include "Encoder.h"

volatile int32_t ENC1_Base, ENC2_Base;  

void Encoder1_Init( void )/* TIM2 */
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef	TIM_ICInitStructure;

	/* TIM4 clock source enable */
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
	/* Enable GPIOB, clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );

	/* Configure PB.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	/* Enable the TIM4 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );

	/* Timer configuration in Encoder mode */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;                 /* No prescaling */
	TIM_TimeBaseStructure.TIM_Period = 10000;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );

	TIM_ICInitStructure.TIM_ICFilter = 1;
	TIM_ICInit( TIM2, &TIM_ICInitStructure );
	TIM_EncoderInterfaceConfig( TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising );

	/* Clear all pending interrupts */
	TIM_ClearFlag( TIM2, TIM_FLAG_Update );
	TIM_ITConfig( TIM2, TIM_IT_Update, ENABLE );
	/* Reset counter */
	TIM2->CNT = 0;

	/* ENC_Clear_Speed_Buffer(); */
	TIM_Cmd( TIM2, ENABLE );
}


int32_t get_ENC1_Count( void )
{
	int32_t ENC_Count;
	ENC_Count = (int32_t) (TIM2->CNT) + ENC1_Base;
#ifdef  ENC1_DIRECT_INVERSE
	return(ENC_Count);
#else
	return(-ENC_Count);
#endif
}


void Encoder2_Init( void )/* TIM4 */
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef	TIM_ICInitStructure;

	/* TIM4 clock source enable */
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );
	/* Enable GPIOB, clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

	/* Configure PB.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	/* Enable the TIM4 Update Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );

	/* Timer configuration in Encoder mode */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;                 /* No prescaling */
	TIM_TimeBaseStructure.TIM_Period = 10000;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure );

	TIM_ICInitStructure.TIM_ICFilter = 1;
	TIM_ICInit( TIM4, &TIM_ICInitStructure );
	TIM_EncoderInterfaceConfig( TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising );

	/* Clear all pending interrupts */
	TIM_ClearFlag( TIM4, TIM_FLAG_Update );
	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE );
	/* Reset counter */
	TIM4->CNT = 0;

	/* ENC_Clear_Speed_Buffer(); */
	TIM_Cmd( TIM4, ENABLE );
}


int32_t get_ENC2_Count( void )
{
	int32_t ENC_Count;
	ENC_Count = (int32_t) (TIM4->CNT) + ENC2_Base;
#ifdef  ENC2_DIRECT_INVERSE
	return(ENC_Count);
#else
	return(-ENC_Count);
#endif
}

void Clear_ENC1_Count( void )
{
	TIM2->CNT = 0;
	ENC1_Base = 0;
}

void Clear_ENC2_Count( void )
{
	TIM4->CNT = 0;
	ENC2_Base = 0;
}


