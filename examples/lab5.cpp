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

   string send = "Taichung City\n" ;
   
   uart.uartWrite(send.c_str(), send.length()) ;
   uart.uartClose() ;

   return 0;
}