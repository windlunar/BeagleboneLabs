/**
 * Lab5
 */ 

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../peripheral/include/uart.h"

using namespace std ;


int main(int argc, char *argv[]){
   UART uart(4) ;

   char writeBuf[1] = {0} ; 
   writeBuf[0] = *argv[1] ;  
   char readBuf[2] = {0} ;   
   
   uart.uartWrite(writeBuf, 1) ;
   uart.uartRead(readBuf, 2) ;
   printf("%x\n" ,readBuf[0]) ;
   printf("%x\n" ,readBuf[1]) ;
   uart.uartClose() ;

   return 0;
}