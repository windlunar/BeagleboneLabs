#ifndef __PWM_H_
#define __PWM_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <cstdlib>

//using namespace std;

#define PWM_PATH "/sys/class/pwm/"

/** For Beaglebone black with Debian*/
//#define P9_14 "pwm-3:0"  


/** For Beaglebone black with Ubuntu 18.04.4 LTS,Image 2020-03-12*/
#define P9_22  "pwm-1:0"
#define P9_21  "pwm-1:1"

#define P9_14  "pwm-4:0"
#define P9_16  "pwm-4:1"

#define P8_19  "pwm-7:0"
#define P8_13  "pwm-7:1"

#define PWM_PERIOD "period"
#define PWM_DUTY "duty_cycle"
#define PWM_ENABLE "enable"


class PWM{
   private:
      std::string pin, path;
      int32_t write(std::string path, std::string filename, std::string value);

   public:
	   PWM(std::string pin);
      PWM(int chip ,int channel) ;

      void configPeriod(std::string periodNS);
      void configDutyCycle(std::string dutyNS) ;
      void enable();

      void setFreq_and_DutyCycle(int Hz ,float dutyCycle);

      ~PWM();
};


#endif