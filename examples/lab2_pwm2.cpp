#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../peripheral/include/pwm.h"

using namespace std;


int main(int argc, char* argv[]){
   cout << "Starting the program" << endl;

   PWM *pwm1 = new PWM(P9_14) ;
   PWM *pwm2 = new PWM(P9_16) ;

   pwm1->configPeriod("20000000") ;
   pwm1->configDutyCycle("16000000");

   pwm2->configPeriod("20000000") ;
   pwm2->configDutyCycle("16000000");

   pwm1->disable();
   pwm2->enable();
   usleep(3000000) ;

   pwm2->disable();
   pwm1->enable();
   usleep(3000000) ;

   pwm1->disable();


   delete pwm1 ;
   delete pwm2 ;

   cout << "Finished the lab2 program" << endl;
   return 0;
}