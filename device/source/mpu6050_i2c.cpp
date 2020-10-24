
#include "../include/mpu6050_i2c.h"



using namespace std;

MPU6050_I2C::MPU6050_I2C(I2CDEV *i2c_ptr){
    i2c = i2c_ptr ;

	this->rawAccelX = 0;
	this->rawAccelY = 0;
	this->rawAccelZ = 0;

	this->rawGyroX = 0 ;
	this->rawGyroY = 0 ;
	this->rawGyroZ = 0 ;

	this->accel_range = ACCEL_RANGE_4_G;
	this->gyro_range = GYRO_RANGE_1000_DEGREE;

	mpuInit();
}

void MPU6050_I2C::mpuInit(){
	cout << "Initialize MPU6050..." << endl ;
	// bit[4] : I2C_IF_DIS
	// MPU-6050: Always write this bit as zero.
	uint8_t user_ctrl_val = readReg(reg.USER_CTRL) ;
	user_ctrl_val &= ~(1 << 4) ;

	printf("Write 0x%x to USER_CTRL, always write 0 to bit[4].\n" ,user_ctrl_val) ;
	writeReg(reg.USER_CTRL, user_ctrl_val) ;


	/* Init clock source and clear sleep bit(bit 6)**/
	uint8_t pwr_mgmt1_val = readReg(reg.PWR_MGMT_1) ;
	pwr_mgmt1_val |=  (uint8_t)CLKSEL_PLL_GYRO_X ;
	pwr_mgmt1_val &= ~( (uint8_t)(1 << 6) ) ;	//clear sleep bit

	printf("Write 0x%x to PWR_MGMT_1, to set clock source as PLL_GYRO_X and disable sleep mode.\n" ,pwr_mgmt1_val) ;
	writeReg(reg.PWR_MGMT_1 ,pwr_mgmt1_val) ;


	/** Set Gyro range*/
	uint8_t gyro_config_val = readReg(reg.GYRO_CONFIG) ;
	gyro_config_val |= (uint8_t)(gyro_range << 3) ;

	printf("Write 0x%x to GYRO_CONFIG, set gyro full scale range.\n" ,gyro_config_val) ;
	writeReg(reg.GYRO_CONFIG ,gyro_config_val) ;


	/** Set Accel range*/
	uint8_t accel_config_val = readReg(reg.ACCEL_CONFIG) ;
	accel_config_val |= (uint8_t)(accel_range << 3) ;

	printf("Write 0x%x to ACCEL_CONFIG, set Accel full scale range.\n" ,accel_config_val) ;
	writeReg(reg.ACCEL_CONFIG ,accel_config_val) ;

	/** Check if MPU6050 id = 0x68*/
	uint8_t mpuID = getMPU6050_ID();
	if( mpuID != 0x68 ){
		cout << "Wrong mpu6050 ID number!" << endl  ;
		exit(1) ;
	}
	printf("Read MPU6050's ID : 0x%x ,Correct!\n" ,mpuID) ;
	cout << "Initialize done!\n" << endl ;
}


//Default ID should be 0x68
uint8_t MPU6050_I2C::getMPU6050_ID(){
	return readReg(reg.WHO_AM_I) ;
}


int32_t MPU6050_I2C::writeReg(uint8_t regAddr, uint8_t value){
	uint8_t send[2] = {0} ;
	send[0] = regAddr ;
	send[1] = value ;

	i2c->writeBuf(send, 2) ;
	return 0;
}


uint8_t MPU6050_I2C::readReg(uint8_t regAddr){
	i2c->i2c_Write(regAddr) ;
	uint8_t receive = i2c->i2c_Read() ;

	return receive;
}




short MPU6050_I2C::combine_MSB_LSB(uint8_t msByte, uint8_t lsByte){
	//
   return ((short)msByte << 8) | (short)lsByte ;
}


int32_t MPU6050_I2C::getRawGyro(){

	calculate_GyroXYZ() ;
	return 0;
}


void MPU6050_I2C::calculate_GyroXYZ(){


}



void MPU6050_I2C::print_GyroXYZ(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "accel_X(g): " << fixed << setprecision(4) << Gyro_X 
		  		<< " ;  accel_Y(g): " << fixed << setprecision(4) << Gyro_Y 
				<< " ;  accel_Z(g): " << fixed << setprecision(4) << Gyro_Z 
				<< "     \r" << flush;
	      usleep(100000);
		  getRawGyro() ;
	}
}

int32_t MPU6050_I2C::getRawAccel(){

	return 0;
}


void MPU6050_I2C::calculate_AccelXYZ_g(){
	float gravity_range = 4.0f; 
    float resol = 1024.0f;	//10-bit
    float factor = gravity_range / resol;

    accelXg = rawAccelX * factor;
    accelYg = rawAccelY * factor;
    accelZg = rawAccelZ * factor;
}



void MPU6050_I2C::print_AccelXYZ(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "accel_X(g): " << fixed << setprecision(4) << accelXg 
		  		<< " ;  accel_Y(g): " << fixed << setprecision(4) << accelYg 
				<< " ;  accel_Z(g): " << fixed << setprecision(4) << accelZg 
				<< "     \r" << flush;
	      usleep(100000);
	      getRawAccel();
	}
}