
#ifndef _MPU6050_REG_H_
#define _MPU6050_REG_H_

#include <stdint.h>

//#define REGS_NUM    0x40

typedef struct{
    uint8_t SELF_TEST_X         = 0x0d ;
    uint8_t SELF_TEST_Y         = 0x0e ;
    uint8_t SELF_TEST_Z         = 0x0f ;
    uint8_t SELF_TEST_A         = 0x10 ;
    uint8_t SMPLRT_DIV          = 0x19 ;
    uint8_t CONFIG              = 0x1a ;
    uint8_t GYRO_CONFIG         = 0x1b ;
    uint8_t ACCEL_CONFIG        = 0x1c ;
    uint8_t FIFO_EN             = 0x23 ;

    uint8_t I2C_MST_CTRL        = 0x24 ;
    uint8_t I2C_SLV0_ADDR       = 0x25 ;
    uint8_t I2C_SLV0_REG        = 0x26 ;
    uint8_t I2C_SLV0_CTRL       = 0x27 ;
    uint8_t I2C_SLV1_ADDR       = 0x28 ;
    uint8_t I2C_SLV1_REG        = 0x29 ;
    uint8_t I2C_SLV1_CTRL       = 0x2a ;
    uint8_t I2C_SLV2_ADDR       = 0x2b ;
    uint8_t I2C_SLV2_REG        = 0x2c ;
    uint8_t I2C_SLV2_CTRL       = 0x2d ;
    uint8_t I2C_SLV3_ADDR       = 0x2e ;
    uint8_t I2C_SLV3_REG        = 0x2f ;
    uint8_t I2C_SLV3_CTRL       = 0x30 ;
    uint8_t I2C_SLV4_ADDR       = 0x31 ;
    uint8_t I2C_SLV4_REG        = 0x32 ;
    uint8_t I2C_SLV4_DO         = 0x33 ;
    uint8_t I2C_SLV4_CTRL       = 0x34 ;
    uint8_t I2C_SLV4_DI         = 0x35 ;
    uint8_t I2C_MST_STATUS      = 0x36 ;

    uint8_t INT_PIN_CFG         = 0x37 ;
    uint8_t INT_ENABLE          = 0x38 ;
    uint8_t INT_STATUS          = 0x3a ;

    uint8_t ACCEL_XOUT_H        = 0x3b ;
    uint8_t ACCEL_XOUT_L        = 0x3c ;
    uint8_t ACCEL_YOUT_H        = 0x3d ;
    uint8_t ACCEL_YOUT_L        = 0x3e ;
    uint8_t ACCEL_ZOUT_H        = 0x3f ;
    uint8_t ACCEL_ZOUT_L        = 0x40 ;
    uint8_t TEMP_OUT_H          = 0x41 ;
    uint8_t TEMP_OUT_L          = 0x42 ;
    uint8_t GYRO_XOUT_H         = 0x43 ;
    uint8_t GYRO_XOUT_L         = 0x44 ;
    uint8_t GYRO_YOUT_H         = 0x45 ;
    uint8_t GYRO_YOUT_L         = 0x46 ;
    uint8_t GYRO_ZOUT_H         = 0x47 ;
    uint8_t GYRO_ZOUT_L         = 0x48 ;

    uint8_t EXT_SENS_DATA_00    = 0x49 ;
    uint8_t EXT_SENS_DATA_01    = 0x4a ;
    uint8_t EXT_SENS_DATA_02    = 0x4b ;
    uint8_t EXT_SENS_DATA_03    = 0x4c ;
    uint8_t EXT_SENS_DATA_04    = 0x4d ;
    uint8_t EXT_SENS_DATA_05    = 0x4e ;
    uint8_t EXT_SENS_DATA_06    = 0x4f ;
    uint8_t EXT_SENS_DATA_07    = 0x50 ;
    uint8_t EXT_SENS_DATA_08    = 0x51 ;
    uint8_t EXT_SENS_DATA_09    = 0x52 ;
    uint8_t EXT_SENS_DATA_10    = 0x53 ;
    uint8_t EXT_SENS_DATA_11    = 0x54 ;
    uint8_t EXT_SENS_DATA_12    = 0x55 ;
    uint8_t EXT_SENS_DATA_13    = 0x56 ;
    uint8_t EXT_SENS_DATA_14    = 0x57 ;
    uint8_t EXT_SENS_DATA_15    = 0x58 ;
    uint8_t EXT_SENS_DATA_16    = 0x59 ;
    uint8_t EXT_SENS_DATA_17    = 0x5a ;
    uint8_t EXT_SENS_DATA_18    = 0x5b ;
    uint8_t EXT_SENS_DATA_19    = 0x5c ;
    uint8_t EXT_SENS_DATA_20    = 0x5d ;
    uint8_t EXT_SENS_DATA_21    = 0x5e ;
    uint8_t EXT_SENS_DATA_22    = 0x5f ;
    uint8_t EXT_SENS_DATA_23    = 0x60 ;

    uint8_t I2C_SLV0_DO         = 0x63 ;
    uint8_t I2C_SLV1_DO         = 0x64 ;
    uint8_t I2C_SLV2_DO         = 0x65 ;
    uint8_t I2C_SLV3_DO         = 0x66 ;
    uint8_t I2C_MST_DELAY_CTRL  = 0x67 ;

    uint8_t SIGNAL_PATH_RESET   = 0x68 ;
    uint8_t USER_CTRL           = 0x6a ;
    uint8_t PWR_MGMT_1          = 0x6b ;
    uint8_t PWR_MGMT_2          = 0x6c ;
    uint8_t FIFO_COUNTH         = 0x72 ;
    uint8_t FIFO_COUNTL         = 0x73 ;
    uint8_t FIFO_R_W            = 0x74 ;
    uint8_t WHO_AM_I            = 0x75 ;

}MPU6050_REG_t;


#define CLKSEL_INTERNAL_OSC     0
#define CLKSEL_PLL_GYRO_X       1
#define CLKSEL_PLL_GYRO_Y       2
#define CLKSEL_PLL_GYRO_Z       3
#define CLKSEL_EXT_32_768KHZ    4
#define CLKSEL_EXT_19_MHZ       5
#define CLKSEL_STOP             7



#define GYRO_RANGE_250_DEGREE   0   // +/-  250 degree/sec
#define GYRO_RANGE_500_DEGREE   1   // +/-  500 degree/sec
#define GYRO_RANGE_1000_DEGREE  2   // +/-  1000 degree/sec
#define GYRO_RANGE_2000_DEGREE  3   // +/-  2000 degree/sec

#define ACCEL_RANGE_2_G   0   // +/-  2G
#define ACCEL_RANGE_4_G   1   // +/-  4G
#define ACCEL_RANGE_8_G   2    // +/- 8G
#define ACCEL_RANGE_16_G  3   // +/-  16G



#endif