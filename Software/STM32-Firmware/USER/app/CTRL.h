#ifndef _CTRL_H_
#define _CTRL_H_

#include "stm32f10x.h"
#include "myInclude.h"
#include "Robot.h"

typedef struct
{
	double		q1, q2, q3,q4;
	double		Setpoint, Output, Integral, last_error;
	uint32_t	timer;
} CTRL;

extern CTRL	CTRL_AngleX, CTRL_AngleY, CTRL_SpeedX,CTRL_SpeedY;
extern double	RELAX_ANGLEX, RELAX_ANGLEY;

void CTRL_compute_AngleX(void);


void CTRL_compute_SpeedX(void);


void CTRL_compute_AngleY(void);


void CTRL_compute_SpeedY(void);


#endif
