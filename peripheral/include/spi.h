#ifndef __SPI_H_
#define __SPI_H_

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SPIDEV_PATH "/dev/spidev"

using namespace std ;

#define MODE0   0
#define MODE1   1
#define MODE2   2
#define MODE3   3

class SPIDEV{
    public:
        SPIDEV(uint32_t SPIbus, uint32_t cs_num);

        int32_t openSPI();
        void closeSPI();
        int32_t PutAndGet(uint8_t *put, uint8_t *get, int32_t length) ;
        
        ~SPIDEV(){};

    private:
        //spidevX.Y ,X:bus number ,Y:device number
        uint32_t SPIbus ;
        uint32_t cs_num ;
        string path ;

        uint32_t SPIspeed ;
        uint8_t bitsPerFrame ;
        int32_t SPImode ;
        uint32_t SPIdelay ;

        int32_t fp;

        int32_t setConfig() ;
};

#endif