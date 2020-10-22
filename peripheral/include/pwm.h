#ifndef __PWM_H_
#define __PWM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>

//using namespace std;

#define PWM_PATH "/sys/class/pwm/"
#define P9_14 "pwm-3:0"

#define PWM_PERIOD "period"
#define PWM_DUTY "duty_cycle"
#define PWM_RUN "enable"


class PWM{
   private:
      std::string name, path;
      int32_t write(std::string path, std::string filename, std::string value);

   public:
	   PWM(std::string pinName);
      void setPeriod(std::string period_ns);
      void setDutyCycle(std::string duty_ns) ;
      void run();
      ~PWM();
};


#endif