#include "MPU6050.h"

int16_t AccelGyro[6]={ 0 };


/** Power on and prepare for general usage.
 * This will activate the device and take it out of sleep mode (which must be done
 * after start-up). This function also sets both the accelerometer and the gyroscope
 * to their most sensitive settings, namely +/- 2g and +/- 250 degrees/sec, and sets
 * the clock source to use the X Gyro for reference, which is slightly better than
 * the default internal clock source.
 */
void MPU6050_Init()
{
	DIS_SYSTICK();
	
	MPU6050_I2C_Init();
	if( !MPU6050_TestConnection() )
	{
		printf( "init error\r\n" );
		while( 1 ) ;
	}
	MPU6050_SetClockSource( MPU6050_CLOCK_PLL_XGYRO );
	MPU6050_SetFullScaleGyroRange( MPU6050_GYRO_FS_2000 );
	MPU6050_SetFullScaleAccelRange( MPU6050_ACCEL_FS_4 );
	MPU6050_SetSleepModeStatus( DISABLE );
	
	EN_SYSTICK();
}


/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, FALSE otherwise
 */
uint8_t MPU6050_TestConnection()
{
	return(MPU6050_GetDeviceID() == 0x34 ? 1 : 0); /* 0b110100; 8-bit representation in hex = 0x34 */
}


/* WHO_AM_I register */


/** Get Device ID.
 * This register is used to verify the identity of the device (0b110100).
 * @return Device ID (should be 0x68, 104 dec, 150 oct)
 * @see MPU6050_RA_WHO_AM_I
 * @see MPU6050_WHO_AM_I_BIT
 * @see MPU6050_WHO_AM_I_LENGTH
 */
uint8_t MPU6050_GetDeviceID()
{
	uint8_t tmp;
	MPU6050_ReadBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &tmp );
	return(tmp);
}


/** Set clock source setting.
 * An internal 8MHz oscillator, gyroscope based clock, or external sources can
 * be selected as the MPU-60X0 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-60X0 can operate
 * in low power modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-60X0 clock source defaults to the internal oscillator.
 * However, it is highly recommended that the device be configured to use one of
 * the gyroscopes (or an external clock source) as the clock reference for
 * improved stability. The clock source can be selected according to the following table:
 *
 * <pre>
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
 * </pre>
 *
 * @param source New clock source setting
 * @see MPU6050_GetClockSource()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_CLKSEL_BIT
 * @see MPU6050_PWR1_CLKSEL_LENGTH
 */
void MPU6050_SetClockSource( uint8_t source )
{
	MPU6050_WriteBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source );
}


/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see MPU6050_GetFullScaleGyroRange()
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
void MPU6050_SetFullScaleGyroRange( uint8_t range )
{
	MPU6050_WriteBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range );
}


/* GYRO_CONFIG register */


/** Get full-scale gyroscope range.
 * The FS_SEL parameter allows setting the full-scale range of the gyro sensors,
 * as described in the table below.
 *
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
 *
 * @return Current full-scale gyroscope range setting
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
uint8_t MPU6050_GetFullScaleGyroRange()
{
	uint8_t tmp;
	MPU6050_ReadBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, &tmp );
	return(tmp);
}


/** Get full-scale accelerometer range.
 * The FS_SEL parameter allows setting the full-scale range of the accelerometer
 * sensors, as described in the table below.
 *
 * <pre>
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 * </pre>
 *
 * @return Current full-scale accelerometer range setting
 * @see MPU6050_ACCEL_FS_2
 * @see MPU6050_RA_ACCEL_CONFIG
 * @see MPU6050_ACONFIG_AFS_SEL_BIT
 * @see MPU6050_ACONFIG_AFS_SEL_LENGTH
 */
uint8_t MPU6050_GetFullScaleAccelRange()
{
	uint8_t tmp;
	MPU6050_ReadBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, &tmp );
	return(tmp);
}


/** Set full-scale accelerometer range.
 * @param range New full-scale accelerometer range setting
 * @see MPU6050_GetFullScaleAccelRange()
 */
void MPU6050_SetFullScaleAccelRange( uint8_t range )
{
	MPU6050_WriteBits( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range );
}


/** Get sleep mode status.
 * Setting the SLEEP bit in the register puts the device into very low power
 * sleep mode. In this mode, only the serial interface and internal registers
 * remain active, allowing for a very low standby current. Clearing this bit
 * puts the device back into normal mode. To save power, the individual standby
 * selections for each of the gyros should be used if any gyro axis is not used
 * by the application.
 * @return Current sleep mode enabled status
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_SLEEP_BIT
 */
uint8_t MPU6050_GetSleepModeStatus()
{
	uint8_t tmp;
	MPU6050_ReadBit( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, &tmp );
	return(tmp == 0x00 ? 0 : 1);
}


/** Set sleep mode status.
 * @param enabled New sleep mode enabled status
 * @see MPU6050_GetSleepModeStatus()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_SLEEP_BIT
 */
void MPU6050_SetSleepModeStatus( FunctionalState NewState )
{
	MPU6050_WriteBit( MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, NewState );
}


/** Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param AccelGyro 16-bit signed integer array of length 6
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
void MPU6050_PollRawAccelGyro( void )
{
	u8	tmpBuffer[14];
	int	i;
	
	DIS_SYSTICK();
	MPU6050_I2C_BufferRead( MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14 );
	EN_SYSTICK();
	/* Get acceleration */
	for( i = 0; i < 3; i++ )
		AccelGyro[i] = ( (s16) ( (u16) tmpBuffer[2 * i] << 8) + tmpBuffer[2 * i + 1]);
	/* Get Angular rate */
	for( i = 4; i < 7; i++ )
		AccelGyro[i - 1] = ( (s16) ( (u16) tmpBuffer[2 * i] << 8) + tmpBuffer[2 * i + 1]);
}


/** Write multiple bits in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 */
void MPU6050_WriteBits( uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data )
{
	/*
	 *      010 value to write
	 * 76543210 bit numbers
	 *    xxx   args: bitStart=4, length=3
	 * 00011100 mask byte
	 * 10101111 original value (sample)
	 * 10100011 original & ~mask
	 * 10101011 masked | value
	 */
	uint8_t tmp, mask;
	MPU6050_I2C_BufferRead( slaveAddr, &tmp, regAddr, 1 );
	mask = ( (1 << length) - 1) << (bitStart - length + 1);
	data <<= (bitStart - length + 1);       /* shift data into correct position */
	data &= mask;                           /* zero all non-important bits in data */
	tmp &= ~(mask);                         /* zero all important bits in existing byte */
	tmp |= data;                            /* combine data with existing byte */
	MPU6050_I2C_ByteWrite( slaveAddr, &tmp, regAddr );
}


/** write a single bit in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 */
void MPU6050_WriteBit( uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data )
{
	uint8_t tmp;
	MPU6050_I2C_BufferRead( slaveAddr, &tmp, regAddr, 1 );
	tmp = (data != 0) ? (tmp | (1 << bitNum) ) : (tmp & ~(1 << bitNum) );
	MPU6050_I2C_ByteWrite( slaveAddr, &tmp, regAddr );
}


/** Read multiple bits from an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in readTimeout)
 */
void MPU6050_ReadBits( uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data )
{
	/*
	 * 01101001 read byte
	 * 76543210 bit numbers
	 *    xxx   args: bitStart=4, length=3
	 *    010   masked
	 *   -> 010 shifted
	 */
	uint8_t tmp, mask;
	MPU6050_I2C_BufferRead( slaveAddr, &tmp, regAddr, 1 );
	mask = ( (1 << length) - 1) << (bitStart - length + 1);
	tmp &= mask;
	tmp >>= (bitStart - length + 1);
	*data = tmp;
}


/** Read a single bit from an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in readTimeout)
 */
void MPU6050_ReadBit( uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data )
{
	uint8_t tmp;
	MPU6050_I2C_BufferRead( slaveAddr, &tmp, regAddr, 1 );
	*data = tmp & (1 << bitNum);
}


/**
 * @brief  Initializes the I2C peripheral used to drive the MPU6050
 * @param  None
 * @return None
 */
void MPU6050_I2C_Init()
{
	I2C_InitTypeDef		I2C_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	I2C_DeInit( I2C2 );

	/* Enable I2C and GPIO clocks */
	RCC_APB1PeriphClockCmd( MPU6050_I2C_RCC_Periph, ENABLE );
	RCC_APB2PeriphClockCmd( MPU6050_I2C_RCC_Port, ENABLE );

	/* Configure I2C pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin = MPU6050_I2C_SCL_Pin | MPU6050_I2C_SDA_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init( MPU6050_I2C_Port, &GPIO_InitStructure );

	/* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = MPU6050_DEFAULT_ADDRESS; /* MPU6050 7-bit adress = 0x68, 8-bit adress = 0xD0; */
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = MPU6050_I2C_Speed;

	/* Apply I2C configuration after enabling it */
	I2C_Init( MPU6050_I2C, &I2C_InitStructure );
	/* I2C Peripheral Enable */
	I2C_Cmd( MPU6050_I2C, ENABLE );
}


/**
 * @brief  Writes one byte to the  MPU6050.
 * @param  slaveAddr : slave address MPU6050_DEFAULT_ADDRESS
 * @param  pBuffer : pointer to the buffer  containing the data to be written to the MPU6050.
 * @param  writeAddr : address of the register in which the data will be written
 * @return None
 */
void MPU6050_I2C_ByteWrite( u8 slaveAddr, u8* pBuffer, u8 writeAddr )
{
	/* ENTR_CRT_SECTION(); */

	/* Send START condition */
	I2C_GenerateSTART( MPU6050_I2C, ENABLE );

	/* Test on EV5 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_MODE_SELECT ) ) ;

	/* Send MPU6050 address for write */
	I2C_Send7bitAddress( MPU6050_I2C, slaveAddr, I2C_Direction_Transmitter );

	/* Test on EV6 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ) ;

	/* Send the MPU6050's internal address to write to */
	I2C_SendData( MPU6050_I2C, writeAddr );

	/* Test on EV8 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ) ;

	/* Send the byte to be written */
	I2C_SendData( MPU6050_I2C, *pBuffer );

	/* Test on EV8 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ) ;

	/* Send STOP condition */
	I2C_GenerateSTOP( MPU6050_I2C, ENABLE );

	/* EXT_CRT_SECTION(); */
}


/**
 * @brief  Reads a block of data from the MPU6050.
 * @param  slaveAddr  : slave address MPU6050_DEFAULT_ADDRESS
 * @param  pBuffer : pointer to the buffer that receives the data read from the MPU6050.
 * @param  readAddr : MPU6050's internal address to read from.
 * @param  NumByteToRead : number of bytes to read from the MPU6050 ( NumByteToRead >1  only for the Mgnetometer readinf).
 * @return None
 */
void MPU6050_I2C_BufferRead( u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead )
{
	/* ENTR_CRT_SECTION(); */

	/* While the bus is busy */
	while( I2C_GetFlagStatus( MPU6050_I2C, I2C_FLAG_BUSY ) ) ;

	/* Send START condition */
	I2C_GenerateSTART( MPU6050_I2C, ENABLE );

	/* Test on EV5 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_MODE_SELECT ) ) ;

	/* Send MPU6050 address for write */
	I2C_Send7bitAddress( MPU6050_I2C, slaveAddr, I2C_Direction_Transmitter );

	/* Test on EV6 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ) ;

	/* Clear EV6 by setting again the PE bit */
	I2C_Cmd( MPU6050_I2C, ENABLE );

	/* Send the MPU6050's internal address to write to */
	I2C_SendData( MPU6050_I2C, readAddr );

	/* Test on EV8 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ) ;

	/* Send STRAT condition a second time */
	I2C_GenerateSTART( MPU6050_I2C, ENABLE );

	/* Test on EV5 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_MODE_SELECT ) ) ;

	/* Send MPU6050 address for read */
	I2C_Send7bitAddress( MPU6050_I2C, slaveAddr, I2C_Direction_Receiver );

	/* Test on EV6 and clear it */
	while( !I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) ) ;

	/* While there is data to be read */
	while( NumByteToRead )
	{
		if( NumByteToRead == 1 )
		{
			/* Disable Acknowledgement */
			I2C_AcknowledgeConfig( MPU6050_I2C, DISABLE );

			/* Send STOP Condition */
			I2C_GenerateSTOP( MPU6050_I2C, ENABLE );
		}

		/* Test on EV7 and clear it */
		if( I2C_CheckEvent( MPU6050_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED ) )
		{
			/* Read a byte from the MPU6050 */
			*pBuffer = I2C_ReceiveData( MPU6050_I2C );

			/* Point to the next location where the byte read will be saved */
			pBuffer++;

			/* Decrement the read bytes counter */
			NumByteToRead--;
		}
	}

	/* Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig( MPU6050_I2C, ENABLE );
	/* EXT_CRT_SECTION(); */
}


/**
 * @}
 *//* end of group MPU6050_Library */
