#ifndef __SPI_H_
#define __SPI_H_

#include <cstdint>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPIDEV_PATH "/dev/spidev"
using namespace std ;

#define MODE0   0
#define MODE1   1
#define MODE2   2
#define MODE3   3

class SPIDEV{
    public:
        SPIDEV(uint32_t bus, uint32_t device);

        int32_t openSPI();
        void closeSPI();
        int32_t PutAndGet(uint8_t *put, uint8_t *get, int32_t length) ;

        int32_t setSpeed(uint32_t speed) ;
        int32_t setBitsPerWord(uint8_t bits) ;
        int32_t setMode(int32_t mode) ;

        
        ~SPIDEV(){};

    private:
        //spidevX.Y ,X:bus number ,Y:device number
        uint32_t bus ;
        uint32_t device ;
        string path ;

        uint32_t speed ;
        uint8_t bitsPerFrame ;
        int32_t mode ;
        uint32_t delay ;

        int32_t fp;
};

#endif