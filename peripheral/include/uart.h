
#ifndef  __UART_H_
#define  __UART_H_

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
#include <iomanip>


#define UART_PATH   "/dev/ttyS"
#define BUF_SIZE 4096 


using namespace std ;

class UART{
   private:
      string devpath ;
   public:
      int fd;
      UART(int uartdev) ;
      void uartClose();
      int uartOpen();
      int uartWrite(const char *writeBuf, int len);
      int uartRead(char *readBuf, int len);
      int putChar(char ch) ;
      int getChar(char *readBuf) ;
      ~UART();
};

void printProgress(int count, unsigned long filesize) ;

#endif