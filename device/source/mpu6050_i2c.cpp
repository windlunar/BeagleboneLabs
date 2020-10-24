
/**
 * Maintainer : Allen Lin
 */ 

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
	this->gyro_range = GYRO_RANGE_500_DEGREE;

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

	//clear bit3 bit4
	gyro_config_val &= ~( (uint8_t)(0x03 << 3) ) ;	

	//set bit3 bit4
	gyro_config_val |= (uint8_t)(gyro_range << 3) ;	

	printf("Write 0x%x to GYRO_CONFIG, set gyro full scale range.\n" ,gyro_config_val) ;
	writeReg(reg.GYRO_CONFIG ,gyro_config_val) ;


	/** Set Accel range*/
	uint8_t accel_config_val = readReg(reg.ACCEL_CONFIG) ;

	//clear bit3 bit4
	accel_config_val &= ~( (uint8_t)(0x03 << 3) ) ;	

	//set bit3 bit4
	accel_config_val |= (uint8_t)(accel_range << 3) ; 

	printf("Write 0x%x to ACCEL_CONFIG, set Accel full scale range.\n" ,accel_config_val) ;
	writeReg(reg.ACCEL_CONFIG ,accel_config_val) ;

	/** Check if MPU6050 id = 0x68*/
	uint8_t mpuID = getID();
	if( mpuID != 0x68 ){
		cout << "Wrong mpu6050 ID number!" << endl  ;
		exit(1) ;
	}
	printf("Read MPU6050's ID : 0x%x ,Correct!\n" ,mpuID) ;
	cout << "Initialize done!\n" << endl ;
}


//Default ID should be 0x68
uint8_t MPU6050_I2C::getID(){
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




short MPU6050_I2C::combine_MSB_LSB(uint8_t msByte, uint8_t lsByte)
{
   return ((short)msByte << 8) | (short)lsByte ;
}


int32_t MPU6050_I2C::getGyro(){
	uint8_t *gyro_raw = new uint8_t[6] ;

	for(int i =0 ; i < 5 ; i++){
		gyro_raw[i] = readReg( (reg.GYRO_XOUT_H) + i ) ;
	}

	rawGyroX = combine_MSB_LSB(gyro_raw[0],gyro_raw[1]) ;
	rawGyroY = combine_MSB_LSB(gyro_raw[2],gyro_raw[3]) ;
	rawGyroZ = combine_MSB_LSB(gyro_raw[4],gyro_raw[5]) ;

	calRawGyro() ;
	delete gyro_raw ;

	return 0;
}


void MPU6050_I2C::calRawGyro(){
	float fullScaleRange ;
	switch(gyro_range){
		case 1 :
			fullScaleRange = 500.0f ;
			break ;
		case 2 :
			fullScaleRange = 1000.0f ;
			break ;
		case 3 :
			fullScaleRange = 2000.0f ;
			break ;
		default:
			fullScaleRange = 250.0f ;
			break ;
	}

    int resol = 32768;	//16-bit

	Gyro_X = ( (float)rawGyroX * (float)fullScaleRange )/(float)resol ;
    Gyro_Y = ( (float)rawGyroY * (float)fullScaleRange )/(float)resol ;
    Gyro_Z = ( (float)rawGyroZ * (float)fullScaleRange )/(float)resol ;

}



void MPU6050_I2C::print_Gyro(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "[ gyro_x ,gyro_y ,gyro_z ] : [" << fixed << setprecision(4) << Gyro_X 
		  		<< " ," << fixed << setprecision(4) << Gyro_Y 
				<< " ," << fixed << setprecision(4) << Gyro_Z 
				<< " ]     \r" << endl ;//flush;
	      usleep(100000);
		  getGyro() ;
	}
}

int32_t MPU6050_I2C::getAccel(){
	uint8_t *accel_raw = new uint8_t[6] ;

	for(int i =0 ; i < 5 ; i++){
		accel_raw[i] = readReg( (reg.ACCEL_XOUT_H) + i ) ;
	}

	rawAccelX = combine_MSB_LSB(accel_raw[0],accel_raw[1]) ;
	rawAccelY = combine_MSB_LSB(accel_raw[2],accel_raw[3]) ;
	rawAccelZ = combine_MSB_LSB(accel_raw[4],accel_raw[5]) ;
	
	//printf("ax_raw : %d ,ay_raw : %d ,az_raw : %d \n"
	//		,(int)rawAccelX ,(int)rawAccelY ,(int)rawAccelZ) ;

	calRawAccel() ;
	delete accel_raw ;

	return 0;
}


void MPU6050_I2C::calRawAccel()
{
	float fullScaleRange ;
	switch(accel_range){
		case 1 :
			fullScaleRange = 4.0f ;
			break ;
		case 2 :
			fullScaleRange = 8.0f ;
			break ;
		case 3 :
			fullScaleRange = 16.0f ;
			break ;
		default:
			fullScaleRange = 2.0f ;
			break ;
	}

    int resol = 32768;	//16-bit

	accelXg = ( (float)rawAccelX * (float)fullScaleRange )/(float)resol ;
    accelYg = ( (float)rawAccelY * (float)fullScaleRange )/(float)resol ;
    accelZg = ( (float)rawAccelZ * (float)fullScaleRange )/(float)resol ;

	//printf("ax_g : %f ,ay_g : %f ,az_g : %f \n",accelXg ,accelYg ,accelZg) ;

}



void MPU6050_I2C::print_Accel(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "[ a_x ,a_y ,a_z ] : [" << fixed << setprecision(4) << accelXg 
		  		<< " ," << fixed << setprecision(4) << accelYg 
				<< " ," << fixed << setprecision(4) << accelZg 
				<< " ]     \r" << endl ;//flush;
	      usleep(100000);
	      getAccel();
	}
}