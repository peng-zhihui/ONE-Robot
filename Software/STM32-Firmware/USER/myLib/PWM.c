#include "PWM.h"

void TIM3_PWM_Init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init( GPIOB, &GPIO_InitStructure );


/* ------------------------------------------------------------
 * TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
 * TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
 * TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
 * TIM3 Frequency = 72 KHz.
 * TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
 * TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
 * TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
 * TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
 * ------------------------------------------------------------- */
/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = PWM_ARR;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );

	TIM_ARRPreloadConfig( TIM3, ENABLE );
	TIM_Cmd( TIM3, ENABLE );

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init( TIM3, &TIM_OCInitStructure );
	TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable );

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init( TIM3, &TIM_OCInitStructure );
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable );

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init( TIM3, &TIM_OCInitStructure );
	TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable );
}


void PWM_SetValue( PWM_Chanel Chanel, uint16_t PWM )
{
	if( PWM > 1000 )
		PWM=1000;
	PWM *= PWM_CCR;
	switch( Chanel )
	{
	case PWM_CHANEL1:
		TIM3->CCR1 = PWM;
		break;
	case PWM_CHANEL2:
		TIM3->CCR2 = PWM;
		break;
	case PWM_CHANEL3:
		TIM3->CCR3 = PWM;
		break;
	case PWM_CHANEL4:
		TIM3->CCR4 = PWM;
		break;
	}
}


