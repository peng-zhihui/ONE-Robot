#ifndef _PWM_H_
#define _PWM_H_

#include "stm32f10x.h"
#include "myInclude.h"

#define PWM_FREQ	2000
#define PWM_ARR		72000000 / PWM_FREQ - 1
#define PWM_CCR		72000 / PWM_FREQ

typedef enum
{
	PWM_CHANEL1,    /* PA6 */
	PWM_CHANEL2,    /* PA7 */
	PWM_CHANEL3,    /* PB0 */
	PWM_CHANEL4     /* PB1 */
}PWM_Chanel;

void	TIM3_PWM_Init( void );
void	PWM_SetValue( PWM_Chanel Chanel, uint16_t PWM );


#endif

