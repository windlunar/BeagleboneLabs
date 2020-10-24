/**
 * Maintainer : Allen Lin
 */ 

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../peripheral/include/i2c.h"
#include "../device/include/mpu6050_i2c.h"


using namespace std ;


int main(int argc, char *argv[]){
	if( argc != 2 ){
		cout << "Error : Wrong argument number" << endl ;
		cout << "Please type the uart bus number 0 to 4" << endl ;
		return -1 ;
	}

	I2CDEV i2c(stoi(argv[1]) ,0x68) ;
	MPU6050_I2C mpu6050(&i2c) ;

	//printf("MPU6050 ID : 0x%x\n" ,mpu6050.getMPU6050_ID()) ;
	printf("MPU6050 ID : 0x%x\n" ,mpu6050.readReg(mpu6050.reg.WHO_AM_I)) ;
	printf("MPU6050 USER_CTRL : 0x%x\n" ,mpu6050.readReg(mpu6050.reg.USER_CTRL)) ;
	printf("MPU6050 PWR_MGMT_1 : 0x%x\n" ,mpu6050.readReg(mpu6050.reg.PWR_MGMT_1)) ;
	printf("MPU6050 GYRO_CONFIG : 0x%x\n" ,mpu6050.readReg(mpu6050.reg.GYRO_CONFIG)) ;
	printf("MPU6050 ACCEL_CONFIG : 0x%x\n" ,mpu6050.readReg(mpu6050.reg.ACCEL_CONFIG)) ;

	mpu6050.print_Accel(100) ;
	mpu6050.print_Gyro(100) ;


   	return 0;
}