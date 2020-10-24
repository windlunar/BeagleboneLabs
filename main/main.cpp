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
#include "../device/include/us100_ultrasonic.h"


using namespace std ;


int main(int argc, char *argv[]){
	if( argc != 2 ){
		cout << "Error : Wrong argument number" << endl ;
		cout << "Please type the uart bus number 0 to 4" << endl ;
		return -1 ;
	}

	UART uart(stoi(argv[1])) ;
	
	US100 ultrasonic( &uart ) ;

	ultrasonic.print_dist(1000000) ;


   	return 0;
}