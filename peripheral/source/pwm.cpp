
#include "../include/pwm.h"


using namespace std;


PWM::PWM(string pin) {
	this->pin = pin;
   stringstream ss ;
   ss << PWM_PATH << this->pin << "/" ;
   path = ss.str() ;
}


PWM::PWM(int chip ,int channel) {
   stringstream ss ;
   ss <<  PWM_PATH << "pwm-" << chip << ":" << channel << "/" ;
	
	path = ss.str() ;
}


void PWM::configPeriod(string periodNS){
	write(path, PWM_PERIOD, periodNS);
}


void PWM::configDutyCycle(string dutyNS){
	write(path, PWM_DUTY, dutyNS);
}


void PWM::setFreq(int Hz){
   float T = (float)1 / float(Hz) ;
   this->T_ns = (int)(T * (int)1000000000) ;

   stringstream ss_T ;
   ss_T << T_ns ;
   configPeriod(ss_T.str()) ;
}


void PWM::setDutyCycle(float dutyCycle){
   int DT_ns = (this->T_ns) * ( dutyCycle /(float)100 ) ;
   stringstream ss_DT ;
   ss_DT << DT_ns ;
   configDutyCycle(ss_DT.str()) ;
}


void PWM::enable(){
	write(path, PWM_ENABLE, "1");
}


void PWM::disable(){
	write(path, PWM_ENABLE, "0");
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


