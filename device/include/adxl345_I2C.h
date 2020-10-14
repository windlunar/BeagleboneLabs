#ifndef __ADXL345_I2C_H_
#define __ADXL345_I2C_H_

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <iomanip>

#include "adxl345_reg.h"
#include "../../peripheral/include/i2c.h"



#define PLUSMINUS_2_G   0   //plus/minus 2g
#define PLUSMINUS_4_G   1   //plus/minus 4g
#define PLUSMINUS_8_G   2   //plus/minus 8g
#define PLUSMINUS_16_G  3   //plus/minus 16g

#define NORMAL  0           //10-bit NORMAL resolution
#define HIGH    1           //13-bit HIGH resolution (only available in +/- 16g range.)


class ADXL345_I2C{
    private:
        I2CDEV *i2c ;
        ADXL345_REG_t regSet_t ;

        uint32_t spibus ;
        uint32_t spidevice ;
        
        short rawAccelX, rawAccelY, rawAccelZ;  // raw data
        float accelXg, accelYg, accelZg ;

        uint8_t *regs_data = new uint8_t[REGS_NUM] ;

    public:
        int32_t range ;
        int32_t resolution ;

        void InitRegs();
        int32_t writeReg(uint8_t regAddr, uint8_t value);
        uint8_t readReg(uint8_t regAddr);
	    void readAllRegs();

        int32_t getRawAccel();
        short combine_MSB_LSB(uint8_t msByte, uint8_t lsByte);

        void calculate_AccelXYZ_g() ;
        void print_AccelXYZ(int32_t count);

        ADXL345_I2C(I2CDEV *i2c_ptr) ;
        ~ADXL345_I2C(){
            delete regs_data ;
        };   
  
};



#endif