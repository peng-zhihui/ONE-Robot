#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include "myInclude.h"

#define ADC_CHANEL_NUM 5

__IO extern u16 ADC_ConvertedValue[ADC_CHANEL_NUM]; //转换后数据数组

void ADC1_Init(void);


#endif
