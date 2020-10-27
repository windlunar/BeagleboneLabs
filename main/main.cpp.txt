#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../peripheral/include/pwm.h"
#include "../device/include/L9110S.h"


using namespace std;


int main(int argc, char* argv[]){
   cout << "Starting the program" << endl;

   PWM *pwm1 = new PWM(P9_14) ;
   PWM *pwm2 = new PWM(P9_16) ;

   L9110S motor(pwm1 ,pwm2) ;

   motor.start() ;

   for(int i = 0 ; i<4 ; i++){
      cout << "Speed UP : " << i << endl ;
      motor.speedUp();
      usleep(1000000) ;
   }

   for(int i = 0 ; i<4 ; i++){
      cout << "Speed Down : " << i << endl ;
      motor.speedDown() ;
      usleep(1000000) ;
   }



   cout << "Change rotate direction." << endl ;
   motor.changeRotateDirection(REVERSE_ROTATION) ;



   for(int i = 0 ; i<4 ; i++){
      cout << "Speed UP : " << i << endl ;
      motor.speedUp();
      usleep(1000000) ;
   }

   for(int i = 0 ; i<4 ; i++){
      cout << "Speed Down : " << i << endl ;
      motor.speedDown() ;
      usleep(1000000) ;
   }
   

   motor.stop() ;

   delete pwm1 ,pwm2 ;

   return 0;
}