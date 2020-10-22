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
        US100(UART *uart) ;
        ~US100(){} ;
  
};



#endif