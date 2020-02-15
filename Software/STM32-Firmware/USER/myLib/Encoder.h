#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "myInclude.h"

/*
 * #define ENC1_DIRECT_INVERSE
 * #define ENC2_DIRECT_INVERSE
 */

extern volatile int32_t ENC1_Base, ENC2_Base;

void	Encoder1_Init( void );
void	Encoder2_Init( void );
int32_t get_ENC1_Count( void );
int32_t get_ENC2_Count( void );
void Clear_ENC1_Count( void );
void Clear_ENC2_Count( void );


#endif

