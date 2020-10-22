#ifndef __US100_H_
#define __US100_H_

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <iomanip>

#include "../../peripheral/include/uart.h"


class US100{
    private:
        UART *uart ;
        
    public:
        uint32_t temperature ;
        uint32_t range_mm ;
        void us100_range() ;
        void us100_getTemperature() ;
        void print_dist_temp(int32_t count );

        US100(UART *uart) ;
        ~US100(){} ;
};





#endif