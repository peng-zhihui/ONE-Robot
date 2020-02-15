#ifndef _IMU_H_
#define _IMU_H_

#include "stm32f10x.h"
#include "myInclude.h"
#include "Robot.h"

#define ACC_X 0
#define ACC_Y 1
#define ACC_Z 2
#define GYRO_X 3
#define GYRO_Y 4

#define RAD_TO_DEG 64

extern double compAngleX, compAngleY;
extern double  data_convert[5];


void IMU_filter(void);

#endif
