#include "IMU.h"

double	compAngleX, compAngleY;
double	data_convert[5];

void IMU_filter(void)
{
	static uint32_t IMU_timer;
	double		pitch, roll;

	data_convert[0] = ADC_ConvertedValue[ACC_X] - 2100;
	data_convert[1] = ADC_ConvertedValue[ACC_Y] - 2130;
	data_convert[2] = ADC_ConvertedValue[ACC_Z] - 1560;
	data_convert[3] = ADC_ConvertedValue[GYRO_X] - 2035;
	data_convert[4] = ADC_ConvertedValue[GYRO_Y] - 2126;

	pitch	= atan2(data_convert[ACC_X], -data_convert[ACC_Z]) * RAD_TO_DEG;
	roll	= atan2(data_convert[ACC_Y], -data_convert[ACC_Z]) * RAD_TO_DEG;

	compAngleX	= 0.7 * (compAngleX + data_convert[GYRO_Y] * (micros() - IMU_timer) * 0.0000003) - 0.3 * roll;
	compAngleY	= 0.7 * (compAngleY + data_convert[GYRO_X] * (micros() - IMU_timer) * 0.0000003) - 0.3 * pitch;

	IMU_timer = micros();
	
//  printf("%.2f,",compAngleX);
	//printf("%.2f\n",-roll);
	 
}

