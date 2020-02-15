#include "stm32f10x.h"
#include "myInclude.h"
#include "Robot.h"

#define FAILSAFE

int main(void)
{
	double tmp;
	/****************系统初始化****************/
	SysTick_Init();			/* SysTick初始化，配置为系统时钟 */
	USART1_Init();			/* 串口初始化，用于调试 */

	/****************部件初始化****************/
	TIM3_PWM_Init();        /* PWM初始化，使用TIM3配置20KHz频率四通道PWM */
	ADC1_Init();            /* 陀螺仪加速度计初始化，使用DMA传输模式，6通道采样，采样周期55.5个时钟周期 */
	Encoder1_Init();        /* 编码器1初始化，将TIM2配置为正交解码功能 */
	Encoder2_Init();        /* 编码器2初始化，将TIM4配置为正交解码功能 */
	Timer1_Init(5);			/* 将TIM1配置为5ms定时中断，周期性运行控制算法 */

	/****************控制算法参数设置****************/
	CTRL_AngleX.q1	= 300, CTRL_AngleX.q3	= 5, CTRL_SpeedX.q1	= 0.05, CTRL_SpeedX.q2	= 0.8;  
	CTRL_AngleY.q1	= 400, CTRL_AngleY.q2	= 5.5, CTRL_SpeedY.q1	= 0.011, CTRL_SpeedY.q3	= 0.08; 

	/****************准备运行****************/
	while(millis() < 3000);
	
	CTRL_AngleY.Setpoint	= compAngleY;
	RELAX_ANGLEY		= compAngleY;
	FLAG |= A_START; 
	CTRL_AngleX.Setpoint	= compAngleX;
	RELAX_ANGLEX		= compAngleX;

	FLAG |= EC_START;
            
	/****************主循环函数****************/
	while(1)
	{  

	}
}

