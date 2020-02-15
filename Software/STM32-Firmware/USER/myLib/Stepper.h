#ifndef _STEPPER_H_
#define _STEPPER_H_

#include "stm32f10x.h"
#include "myInclude.h"

__IO extern uint32_t stepper_speed_count[3],stepper_speed_need[3];
__IO extern int32_t stepper_pos[3];

#define X 0
#define Y 1
#define Z 2

#define STEPPER0_STEP_SET() GPIOB->BSRR |= GPIO_Pin_9
#define STEPPER0_STEP_RESET() GPIOB->BRR |= GPIO_Pin_9
#define STEPPER0_DIR_SET() GPIOB->BSRR |= GPIO_Pin_5
#define STEPPER0_DIR_RESET() GPIOB->BRR |= GPIO_Pin_5
#define STEPPER0_DIR_READ() GPIOB->IDR & GPIO_Pin_5
#define STEPPER0_EN_SET() GPIOB->BSRR |= GPIO_Pin_8
#define STEPPER0_EN_RESET() GPIOB->BRR |= GPIO_Pin_8

#define STEPPER1_STEP_SET() GPIOB->BSRR |= GPIO_Pin_4
#define STEPPER1_STEP_RESET() GPIOB->BRR |= GPIO_Pin_4
#define STEPPER1_DIR_SET() GPIOA->BSRR |= GPIO_Pin_15
#define STEPPER1_DIR_RESET() GPIOA->BRR |= GPIO_Pin_15
#define STEPPER1_DIR_READ() GPIOA->IDR & GPIO_Pin_15
#define STEPPER1_EN_SET() GPIOB->BSRR |= GPIO_Pin_3
#define STEPPER1_EN_RESET() GPIOB->BRR |= GPIO_Pin_3

#define STEPPER2_STEP_SET() GPIOA->BSRR |= GPIO_Pin_12
#define STEPPER2_STEP_RESET() GPIOA->BRR |= GPIO_Pin_12
#define STEPPER2_DIR_SET() GPIOB->BSRR |= GPIO_Pin_12
#define STEPPER2_DIR_RESET() GPIOB->BRR |= GPIO_Pin_12
#define STEPPER2_DIR_READ() GPIOB->IDR & GPIO_Pin_12
#define STEPPER2_EN_SET() GPIOA->BSRR |= GPIO_Pin_11
#define STEPPER2_EN_RESET() GPIOA->BRR |= GPIO_Pin_11

void Stepper_Init(void);
void Stepper_SetSpeed(uint8_t TYPE,int16_t SPEED);

#endif
