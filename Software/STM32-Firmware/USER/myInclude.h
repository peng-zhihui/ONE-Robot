/***************IO difines*************
 * USART1_TX -> PA9
 * USART1_RX -> PA10
 * USART3_TX -> PB10
 * USART3_RX -> PB11
 * I2C2_SDA -> PB11
 * I2C2_SCL -> PB10
 * I2C1_SDA -> PB7
 * I2C1_SCL -> PB6
 * ADC_Chanel0 -> PA0
 * ADC_Chanel1 -> PA1
 * ADC_Chanel2 -> PA2
 * ADC_Chanel3 -> PA3
 * ADC_Chanel4 -> PA4
 * ADC_Chanel5 -> PA5
 * TIM3_PWM_Chanel1 -> PA6
 * TIM3_PWM_Chanel2 -> PA7
 * TIM3_PWM_Chanel3 -> PB0
 * TIM3_PWM_Chanel4 -> PB1
 * Encoder1_A ->PA0
 * Encoder1_B ->PA1
 * Encoder2_A ->PB6
 * Encoder2_B ->PB7
 ***************************************/
#ifndef __MYINCLUDE_H
#define __MYINCLUDE_H

#include <stdio.h>
#include <math.h>
#include "stdlib.h"
#include "stm32f10x.h"

#include "MPU6050.h"
#include "PWM.h"
#include "Encoder.h"
#include "Timer.h"
#include "ADC.h"


/****************************time*****************************/
#define SYS_PERIOD	10 /* us */
#define SYS_DIV		(uint32_t)(1000000 / SYS_PERIOD)
#define SYS_DELAY	(uint32_t)(1000 / SYS_PERIOD)
#define EN_SYSTICK()	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk
#define DIS_SYSTICK()	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk

extern __IO uint32_t SysTime, TimingDelay;

void SysTick_Init(void);


void delay(__IO uint32_t nTime);


uint32_t millis(void);
uint32_t micros(void);

/****************************serial***************************/
extern uint8_t RxBuffer1,RxBuffer3;

void USART1_Init(void);
void USART3_Init(void);


/****************************gpio*****************************/
typedef enum
{
	LOW,
	HIGH,
	TURN
}GPIO_Level;

void pinMode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode);


void digitalWrite(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Level LEVEL);


uint8_t digitalRead(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif

