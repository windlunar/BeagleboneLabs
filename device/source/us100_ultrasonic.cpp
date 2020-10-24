
#include "../include/us100_ultrasonic.h"



using namespace std;


US100::US100(UART *uartobj){
    this->uart = uartobj ;

    int flags;
    flags = fcntl(uart->fd, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(uart->fd, F_SETFL, flags) == -1){
        perror("Error : Can't change flags!");
        exit(-1);
    }
}

US100::~US100(){
    uart->uartClose() ;
}



int32_t US100::us100_range(){
    string writeVal = "U\n" ; 
    char readBuf_mm[2] = {0} ;
    
    uart->uartWrite(writeVal.c_str(),2) ;
    uart->uartRead(readBuf_mm ,2) ;

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