
#include "../include/us100_ultrasonic.h"



using namespace std;


US100::US100(int uartdev){

    stringstream ss ;
    ss << UART_PATH << uartdev ;
    devpath = ss.str() ;
    fd = uartOpen() ;
}


int US100::uartOpen(){
   if ((fd = open(devpath.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK ))<0){
      perror("Failed to open the UART device.\n");
      return -1;
   }
   /** 
    * struct termios 設定, 參考 uart.cpp 中 int UART::uartOpen()的註解
    */

    struct termios options;
    tcgetattr(fd, &options);

    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    //options.c_cflag |= ~PARENB;     //no parity
    //options.c_cflag |= ~CSTOPB;     //not 2 stop bit
    options.c_iflag = IGNPAR | ICRNL;

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    return fd ;
}


int US100::uartRead(char *readBuf, int len){
    int cnt = -1;
    cnt = read(fd, readBuf, len) ;   
    return cnt ;
}


int32_t US100::us100_range(){
    char writeVal = 0x55 ; 
    char readBuf_mm[2] = {0} ;
    
    uartWrite(&writeVal,1) ;
    uartRead(readBuf_mm ,2) ;

    range_mm = (int32_t)( (readBuf_mm[0] <<8 ) | readBuf_mm[1] ) ;

    if((range_mm < 20) || (range_mm > 250)){
        cout << "Ultrasonic out of range!" << endl ;
        range_mm = -1 ;
    }

    return range_mm ;
}



void US100::print_dist(int32_t count){
	for(int i = 0 ; i < count ; i++){
        if(range_mm != -1){
            cout 	<< "Distance (mm): " << range_mm
				<< "     \r" << endl;
        }
	    usleep(10000);
        us100_range() ;
	}
}