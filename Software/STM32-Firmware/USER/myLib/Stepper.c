#include "stepper.h"

__IO uint32_t	stepper_speed_count[3], stepper_speed_need[3] = { 10000000, 10000000, 10000000 };
__IO int32_t	stepper_pos[3];

void Stepper_Init(void)
{
	pinMode(GPIOB, GPIO_Pin_9, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_8, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            /* 开启AFIO时钟 */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        /* 禁止JTAG功能 */
	pinMode(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP);
	pinMode(GPIOA, GPIO_Pin_15, GPIO_Mode_Out_PP);

	pinMode(GPIOA, GPIO_Pin_12, GPIO_Mode_Out_PP);
	pinMode(GPIOA, GPIO_Pin_11, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_12, GPIO_Mode_Out_PP);
}

void Stepper_SetSpeed(uint8_t TYPE, int16_t SPEED)
{
	if(SPEED > 1000)
	{
		SPEED = 1000;
	}
	else if(SPEED < -1000)
	{
		SPEED = -1000;
	}

	if(SPEED > 0)
	{
		switch(TYPE)
		{
			case 0:
				STEPPER0_DIR_SET();
				break;
			case 1:
				STEPPER1_DIR_SET();
				break;
			case 2:
				STEPPER2_DIR_SET();
				break;
		}
	}
	else if(SPEED < 0)
	{
		SPEED = -SPEED;
		switch(TYPE)
		{
			case 0:
				STEPPER0_DIR_RESET();
				break;
			case 1:
				STEPPER1_DIR_RESET();
				break;
			case 2:
				STEPPER2_DIR_RESET();
				break;
		}
	}

	if(SPEED)
	{
		stepper_speed_need[TYPE] = (uint32_t)(10000 / SPEED);
		stepper_speed_count[TYPE] = stepper_speed_need[TYPE];
	}
	else
	{
		stepper_speed_need[TYPE] = 10000000;
	}
}

