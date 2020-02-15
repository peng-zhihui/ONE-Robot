#include "Timer.h"

void Timer1_Init( uint16_t Period ) //ms
{
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );

	if( Period > 50 )
		Period =50;

	TIM_BaseInitStructure.TIM_Period = (uint16_t) (Period * 1000);
	TIM_BaseInitStructure.TIM_Prescaler = 71;
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit( TIM1, &TIM_BaseInitStructure );

	TIM_ClearFlag( TIM1, TIM_FLAG_Update );
	TIM_ITConfig( TIM1, TIM_IT_Update, ENABLE );
	TIM_Cmd( TIM1, ENABLE );

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );
}


