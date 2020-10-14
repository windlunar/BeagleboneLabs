
#include "../include/pwm.h"


using namespace std;


PWM::PWM(string pinName) {
	this->name = pinName;
	this->path = PWM_PATH + this->name + "/" ;
}

void PWM::setPeriod(string period_ns){
	write(this->path, PWM_PERIOD, period_ns);
}

void PWM::setDutyCycle(string duty_ns){
	write(this->path, PWM_DUTY, duty_ns);
}

void PWM::run(){
	write(this->path, PWM_RUN, "1");
}

int32_t PWM::write(string path, string filename, string value){
   ofstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("Write failed to open file ");
	   return -1;
   }
   fs << value;
   fs.close();
   return 0;
}


PWM::~PWM(){}


