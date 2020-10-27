#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../include/L9110S.h"

using namespace std;



L9110S::L9110S(PWM *pwm_1_ptr ,PWM *pwm_2_ptr){
   this->pwm_f = pwm_1_ptr ;
   this->pwm_r = pwm_2_ptr ;
   pwm_f->setFreq(50) ;
   pwm_r->setFreq(50) ;

   pwm_f->configDutyCycle("0") ;
   pwm_r->configDutyCycle("0") ;

   this->rotateDirection = FORWARD_ROTATION ;

}


void L9110S::speedUp(){
   cout << "rotateDirection : " << rotateDirection << endl ;
   if(rotateDirection == FORWARD_ROTATION){
      if(pwm_f_dutyCycle < 100){
         pwm_f_dutyCycle += 25.0 ;
      }
      
      pwm_f->setDutyCycle(pwm_f_dutyCycle) ;
   }else{
      if(pwm_r_dutyCycle < 100){
         pwm_r_dutyCycle += 25.0 ;
      }
      
      pwm_r->setDutyCycle(pwm_r_dutyCycle) ;
   }
}

void L9110S::speedDown(){
   cout << "rotateDirection : " << rotateDirection << endl ;

   if(rotateDirection == FORWARD_ROTATION){
      if(pwm_f_dutyCycle > 0){
         pwm_f_dutyCycle -= 25.0 ;
      }
      
      pwm_f->setDutyCycle(pwm_f_dutyCycle) ;
   }else{
      if(pwm_r_dutyCycle > 0){
         pwm_r_dutyCycle -= 25.0 ;
      }
      
      pwm_r->setDutyCycle(pwm_r_dutyCycle) ;
   }   
}

void L9110S::changeRotateDirection(int Direction){
   stop() ;
   if(Direction == FORWARD_ROTATION){
      rotateDirection = FORWARD_ROTATION ;
      pwm_f->enable() ;
      pwm_r->disable() ;

   }else{
      rotateDirection = REVERSE_ROTATION ;
      pwm_f->disable() ;
      pwm_r->enable() ;
   }
}

void L9110S::start(){
   pwm_f->enable() ;
   pwm_r->disable() ;

   //pwm_f->disable() ;
   //pwm_r->enable() ;
}

void L9110S::stop(){
   pwm_f->disable() ;
   pwm_r->disable() ;
}


