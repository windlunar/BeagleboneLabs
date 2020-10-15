
#include "../include/i2c.h"


using namespace std;


I2CDEV::I2CDEV(uint32_t bus, uint32_t i2cAddr) {
	this->fp=-1;
	this->bus = bus;
	this->i2cAddr = i2cAddr;
	this->i2c_Open();
}


int32_t I2CDEV::i2c_Open(){
   string path;
   stringstream ss ;
   ss << I2C_PATH << bus ;
   path = ss.str();

   fp = open(path.c_str(), O_RDWR) ;
   if(fp < 0){
      perror("Failed to open I2C\n");
	   return -1 ;
   }
   if(ioctl(fp, I2C_SLAVE, i2cAddr) < 0){
      perror("Failed to connect to I2C\n");
	  return -1;
   }
   return 0;
}


int32_t I2CDEV::writeBuf(uint8_t *sendBuf, int32_t length){
   int count = write(fp, sendBuf, length) ;
   if(count != length){
      perror("Failed to write I2C\n");
      return -1;
   }
   return 0;
}

int32_t I2CDEV::i2c_Write(uint8_t value){
   uint8_t writebuf[1] = {value};
   int count = write(fp, writebuf, 1) ;
   if (count != 1){
      perror("Failed to write I2C\n");
      return -1;
   }
   return 0;
}

uint8_t I2CDEV::i2c_Read(){
   uint8_t buffer[1];
   int count = read(fp, buffer, 1) ;
   if(count != 1){
      perror("Failed to read I2C.\n");
      return -1;
   }
   return buffer[0];
}


int32_t I2CDEV::readBuf(uint32_t length, uint8_t *ReceiveBuf){
   int count = read(fp, ReceiveBuf, length) ;
   if(count != (int)length){
      perror("Failed to read I2C.\n");
      return -1;
   }
   return 0 ;
}

void I2CDEV::i2c_Close(){
	close(fp);
}


I2CDEV::~I2CDEV() {}

