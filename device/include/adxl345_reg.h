
#ifndef _ADXL345_REG_H_
#define _ADXL345_REG_H_

#include <stdint.h>

#define REGS_NUM    0x40

typedef struct{
    uint8_t DEVID            = 0x00 ;
    uint8_t THRESH_TAP       = 0x1D ;
    uint8_t OFSX             = 0x1E ;
    uint8_t OFSY             = 0x1F ;
    uint8_t OFSZ             = 0x20 ;
    uint8_t DUR              = 0x21 ;
    uint8_t Latent           = 0x22 ;
    uint8_t Window           = 0x23 ;
    uint8_t THRESH_ACT       = 0x24 ;
    uint8_t THRESH_INACT     = 0x25 ;
    uint8_t TIME_INACT       = 0x26 ;
    uint8_t ACT_INACT_CTL    = 0x27 ;
    uint8_t THRESH_FF        = 0x28 ;
    uint8_t TIME_FF          = 0x29 ;
    uint8_t TAP_AXES         = 0x2A ;
    uint8_t ACT_TAP_STATUS   = 0x2B ;
    uint8_t BW_RATE          = 0x2C ;
    uint8_t POWER_CTL        = 0x2D ;
    uint8_t INT_ENABLE       = 0x2E ;
    uint8_t INT_MAP          = 0x2F ;
    uint8_t INT_SOURCE       = 0x30 ;
    uint8_t DATA_FORMAT      = 0x31 ;
    uint8_t DATAX0           = 0x32 ;
    uint8_t DATAX1           = 0x33 ;
    uint8_t DATAY0           = 0x34 ;
    uint8_t DATAY1           = 0x35 ;
    uint8_t DATAZ0           = 0x36 ;
    uint8_t DATAZ1           = 0x37 ;
    uint8_t FIFO_CTL         = 0x38 ;
    uint8_t FIFO_STATUS      = 0x39 ;
}ADXL345_REG_t;


#endif