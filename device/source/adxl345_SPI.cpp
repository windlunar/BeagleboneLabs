
#include "../include/adxl345_SPI.h"



using namespace std;

ADXL345_SPI::ADXL345_SPI(SPIDEV *spi_ptr){
    spi = spi_ptr ;

	this->rawAccelX = 0;
	this->rawAccelY = 0;
	this->rawAccelZ = 0;
	this->range = PLUSMINUS_16_G;
	this->resolution = HIGH;
    ////Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
	writeReg((uint8_t)regSet_t.POWER_CTL, (uint8_t)0x08);
	InitRegs();
}

void ADXL345_SPI::InitRegs(){
   //update the DATA_FORMAT register
   uint8_t data_format_val = 0x00;  //+/- 2g with normal resolution
   //Full_resolution is the 3rd LSB
   data_format_val |=  ((uint8_t)resolution << 3) ;
   data_format_val |= (uint8_t)range; // 1st and 2nd LSB therefore no shift
   writeReg(regSet_t.DATA_FORMAT, data_format_val) ;
}


int32_t ADXL345_SPI::writeReg(uint8_t regAddr, uint8_t value){
	uint8_t send[2] = {0} ;
	uint8_t receive[2] = {0} ;
	send[0] = regAddr ;
	send[1] = value ;

	spi->PutAndGet(send, receive, 2);
	return 0;
}


uint8_t ADXL345_SPI::readReg(uint32_t regAddr){
	uint8_t send[2] = {0} ;
    uint8_t receive[2] = {0};

	//Bit 7 = 1 indicates read.
	send[0] = (uint8_t)( (0x01 << 7) | regAddr);
	spi->PutAndGet(send, receive, 2);
	return receive[1];
}


void ADXL345_SPI::readAllRegs(){
    for(uint8_t i = 0 ; i < REGS_NUM ; i++){
        regs_data[i] = readReg(i) ;
    }
}


short ADXL345_SPI::combine_MSB_LSB(uint8_t msByte, uint8_t lsByte){
	//
   return ((short)msByte << 8) | (short)lsByte ;
}

  //讀取ADLX345 的暫存器資料
int32_t ADXL345_SPI::getRawAccel(){
	readAllRegs();
	if(regs_data[0] != 0xe5){
		perror("Error - Wrong ID number. ADXL345 ID should be 0xe5");
		return -1;
	}

	rawAccelX = combine_MSB_LSB(regs_data[regSet_t.DATAX1], regs_data[regSet_t.DATAX0]);
	rawAccelY = combine_MSB_LSB(regs_data[regSet_t.DATAY1], regs_data[regSet_t.DATAY0]);
	rawAccelZ = combine_MSB_LSB(regs_data[regSet_t.DATAZ1], regs_data[regSet_t.DATAZ0]);

	calculate_AccelXYZ_g() ;
	return 0;
}


void ADXL345_SPI::calculate_AccelXYZ_g(){
	float gravity_range;
	switch(range){
		case PLUSMINUS_16_G: 
			gravity_range=32.0f; 
			break;
		case PLUSMINUS_8_G: 
			gravity_range=16.0f; break;
		case PLUSMINUS_4_G: gravity_range=8.0f; 
			break;
		default: 
			gravity_range=4.0f; 
			break;
	}
    float resol = 1024.0f;	//10-bit
    if (resolution == HIGH) resol = 8192.0f; //13-bit
    float factor = gravity_range / resol;

    accelXg = rawAccelX * factor;
    accelYg = rawAccelY * factor;
    accelZg = rawAccelZ * factor;
}



void ADXL345_SPI::print_AccelXYZ(int32_t count){
	for(int i = 0 ; i < count ; i++){
	      cout 	<< "accel_X(g): " << fixed << setprecision(4) << accelXg 
		  		<< " ;  accel_Y(g): " << fixed << setprecision(4) << accelYg 
				<< " ;  accel_Z(g): " << fixed << setprecision(4) << accelZg 
				<< "     \r" << flush;
	      usleep(100000);
	      getRawAccel();
	}
}