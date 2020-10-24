#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../peripheral/include/pwm.h"

using namespace std;


int main(int argc, char* argv[]){
   cout << "Starting the program" << endl;

   PWM *pwm = new PWM(P9_14) ;

   pwm->setPeriod("20000000") ;
   pwm->setDutyCycle("16000000");
   pwm->run();

   delete pwm ;
   cout << "Finished the lab2 program" << endl;
   return 0;
}
