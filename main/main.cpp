#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../peripheral/include/pwm.h"

using namespace std;


int main(int argc, char* argv[]){
   cout << "Starting the program" << endl;
   	if( argc != 3 ){
		cout << "Error : Wrong argument number" << endl ;
		cout << "pwm-x:y, x is the first arg ,y is the second arg." << endl ;
		return -1 ;
	}

   //PWM *pwm = new PWM(P9_14) ;
   PWM *pwm = new PWM(stoi(argv[1]) ,stoi(argv[2])) ;

   pwm->configPeriod("20000000") ;
   pwm->configDutyCycle("16000000");
   pwm->enable();

   delete pwm ;
   cout << "Finished the lab2 program" << endl;
   return 0;
}