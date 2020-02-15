#include "Robot.h"

double		SpeedX,SpeedY;
int32_t		ENC1_Count_last,ENC2_Count_last;
uint32_t	FLAG = 0;

void Robot_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);            /* 开启AFIO时钟 */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);        /* 禁止JTAG功能 */

	pinMode(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP);                  /* LED初始化 */

	/* MotorA */
	pinMode(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_13, GPIO_Mode_Out_PP);
	digitalWrite(GPIOB, GPIO_Pin_3, LOW);
	digitalWrite(GPIOB, GPIO_Pin_13, HIGH);
	PWM_SetValue(PWM_CHANEL3, 0);

	/* MotorB */
	pinMode(GPIOB, GPIO_Pin_12, GPIO_Mode_Out_PP);
	pinMode(GPIOB, GPIO_Pin_14, GPIO_Mode_Out_PP);
	digitalWrite(GPIOB, GPIO_Pin_12, LOW);
	digitalWrite(GPIOB, GPIO_Pin_14, HIGH);
	PWM_SetValue(PWM_CHANEL4, 0);

	/* EC_Motor */
	pinMode(GPIOA, GPIO_Pin_11, GPIO_Mode_Out_PP);  /* EN */
	pinMode(GPIOA, GPIO_Pin_12, GPIO_Mode_Out_PP);  /* DIR */
	digitalWrite(GPIOA, GPIO_Pin_12, HIGH);
	digitalWrite(GPIOA, GPIO_Pin_11, HIGH);
	PWM_SetValue(PWM_CHANEL2, 1000);
}

void MOTOR_A(int SPEED)
{
	if(SPEED > 0)
	{
		digitalWrite(GPIOB, GPIO_Pin_3,HIGH );
		digitalWrite(GPIOB, GPIO_Pin_13, LOW);
		PWM_SetValue(PWM_CHANEL3, SPEED);
	}
	else
	{
		digitalWrite(GPIOB, GPIO_Pin_3, LOW);
		digitalWrite(GPIOB, GPIO_Pin_13, HIGH);
		PWM_SetValue(PWM_CHANEL3, -SPEED);
	}
}

void MOTOR_B(int SPEED)
{
	if(SPEED > 0)
	{
		digitalWrite(GPIOB, GPIO_Pin_12, LOW);
		digitalWrite(GPIOB, GPIO_Pin_14, HIGH);

		PWM_SetValue(PWM_CHANEL4, SPEED);
	}
	else
	{
		digitalWrite(GPIOB, GPIO_Pin_12, HIGH);
		digitalWrite(GPIOB, GPIO_Pin_14, LOW);

		PWM_SetValue(PWM_CHANEL4, -SPEED);
	}
}

void MOTOR_EC(int SPEED)
{
	if(SPEED > 0)
	{
		digitalWrite(GPIOA, GPIO_Pin_12, HIGH);
		PWM_SetValue(PWM_CHANEL2, 1000 - SPEED);
	}
	else
	{
		digitalWrite(GPIOA, GPIO_Pin_12, LOW);
		PWM_SetValue(PWM_CHANEL2, 1000 + SPEED);
	}
}

