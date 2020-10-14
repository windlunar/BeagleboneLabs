#ifndef __PWM_H_
#define __PWM_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>

using namespace std;

#define PWM_PATH "/sys/class/pwm/"
#define P9_14 "pwm-3:0"

#define PWM_PERIOD "period"
#define PWM_DUTY "duty_cycle"
#define PWM_RUN "enable"


class PWM{
   private:
      string name, path;
      int32_t write(string path, string filename, string value);

   public:
	   PWM(string pinName);
      void setPeriod(string period_ns);
      void setDutyCycle(string duty_ns) ;
      void run();
      ~PWM();
};


#endif