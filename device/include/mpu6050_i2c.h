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


/** 
 * For Beaglebone black with Ubuntu 18.04.4 LTS,Image 2020-03-12
 * P9_19 and P9_20 is configure as i2c2 -----> /dev/i2c-2
*/
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
        int32_t gyro_range ;

        void mpuInit();
        int32_t writeReg(uint8_t regAddr, uint8_t value);
        uint8_t readReg(uint8_t regAddr);
        short combine_MSB_LSB(uint8_t msByte, uint8_t lsByte);

        int32_t getAccel();
        int32_t getGyro();

        void calRawAccel() ;
        void calRawGyro() ;

        void print_Accel(int32_t count);
        void print_Gyro(int32_t count);

        uint8_t getID() ;

        MPU6050_I2C(I2CDEV *i2c_ptr) ;
        ~MPU6050_I2C(){}
  
};



#endif