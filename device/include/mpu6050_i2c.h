#ifndef __MPU6050_I2C_H_
#define __MPU6050_I2C_H_

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <iomanip>

#include "mpu6050_reg.h"
#include "../../peripheral/include/i2c.h"


class MPU6050_I2C{
    private:
        I2CDEV *i2c ;
        
        short rawAccelX, rawAccelY, rawAccelZ;  // raw data
        float accelXg, accelYg, accelZg ;

        short rawGyroX, rawGyroY, rawGyroZ;  // raw data
        float Gyro_X, Gyro_Y, Gyro_Z ;

    public:
        MPU6050_REG_t reg ;

        int32_t accel_range ;
        int32_t accel_resolution ;
        int32_t gyro_range ;
        int32_t gyro_resolution ;

        void mpuInit();
        int32_t writeReg(uint8_t regAddr, uint8_t value);
        uint8_t readReg(uint8_t regAddr);
        short combine_MSB_LSB(uint8_t msByte, uint8_t lsByte);

        int32_t getRawAccel();
        int32_t getRawGyro();

        void calculate_AccelXYZ_g() ;
        void calculate_GyroXYZ() ;

        void print_AccelXYZ(int32_t count);
        void print_GyroXYZ(int32_t count);

        uint8_t getMPU6050_ID() ;

        MPU6050_I2C(I2CDEV *i2c_ptr) ;
        ~MPU6050_I2C(){}
  
};



#endif