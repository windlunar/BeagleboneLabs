
#include "../include/us100_ultrasonic.h"



using namespace std;


US100::US100(UART *uart){
    this->uart = uart ;
}

void US100::us100_range(){
    char writeVal = 0x55 ; 
    char readBuf_mm[2] = {0} ;
    
    cout << "us100_range before Write" << endl ;
    uart->uartWrite(&writeVal,1) ;
    cout << "us100_range after Write before read" << endl ;

    uart->uartRead(readBuf_mm ,2) ;
    cout << "us100_range  after Read" << endl ;


    range_mm = (uint32_t)( (readBuf_mm[0] <<8 ) | readBuf_mm[1] ) ;
}


void US100::us100_getTemperature(){
    char writeVal = 0x50 ; 
    char readVal = 0 ;
    
    cout << "us100_getTemperature before Write" << endl ;
    uart->uartWrite(&writeVal,1) ;
    cout << "us100_getTemperature after Write before read" << endl ;

    uart->uartRead(&readVal ,1) ;
    cout << "us100_getTemperature after Read" << endl ;

    readVal -= 0x2D ;
    temperature = (uint32_t)readVal ;
}


void US100::print_dist_temp(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "Distance (mm): " << range_mm
		  		<< " ;  Temperature : " << temperature
				<< "     \r" << endl;
	      usleep(10000);
          us100_range() ;
          us100_getTemperature() ;
	}
}