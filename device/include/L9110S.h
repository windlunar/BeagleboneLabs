#ifndef __L9110S_MOTOR_DRIVE_H_
#define __L9110S_MOTOR_DRIVE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include "../../peripheral/include/pwm.h"

/**
 * LS9110S pin:
 * 
 * B_1 ,B_2 ,GND ,VCC ,A_1 ,A_2
 * 
 */ 

#define FORWARD_ROTATION 0
#define REVERSE_ROTATION 1


class L9110S{
   private:
      int rotateDirection ;
      float pwm_f_dutyCycle ,pwm_r_dutyCycle ;

      PWM *pwm_f; 
      PWM *pwm_r; 

   public:

      L9110S(PWM *pwm_1_ptr ,PWM *pwm_2_ptr);
      void speedUp() ;
      void speedDown() ;
      void changeRotateDirection(int Direction) ;
      void start() ;
      void stop() ;

      ~L9110S(){}

};


#endif