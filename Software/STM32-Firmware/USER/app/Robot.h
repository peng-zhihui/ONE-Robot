#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "stm32f10x.h"
#include "myInclude.h"
#include "CTRL.h"
#include "IMU.h"

#define EC_START 0x0001
#define A_START 0x0002

#define LED_ON()	GPIOC->BRR	|= GPIO_Pin_13
#define LED_OFF()	GPIOC->BSRR	|= GPIO_Pin_13
#define LED_TURN()	GPIOC->ODR ^= GPIO_Pin_13

extern double SpeedX,SpeedY;
extern int32_t ENC1_Count_last,ENC2_Count_last;
extern uint32_t FLAG;
	
void Robot_Init(void);
void MOTOR_A(int SPEED);
void MOTOR_B(int SPEED);
void MOTOR_EC(int SPEED); 

#endif
