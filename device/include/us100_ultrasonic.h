#ifndef __US100_H_
#define __US100_H_

#include <iostream>
#include <unistd.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <iomanip>

#include "../../peripheral/include/uart.h"


class US100 : public UART{
    private:
        UART *uart ;

    public:
        int32_t range_mm ;
        int32_t us100_range() ;
        void print_dist(int32_t count );

        US100(UART *uartobj) ;
        ~US100() ;
};





#endif