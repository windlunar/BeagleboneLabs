
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

   if((fp=open(path.c_str(), O_RDWR)) < 0){
      perror("I2C: failed to open the bus\n");
	  return 1;
   }
   if(ioctl(fp, I2C_SLAVE, this->i2cAddr) < 0){
      perror("I2C: Failed to connect to the device\n");
	  return 1;
   }
   return 0;
}


int32_t I2CDEV::writeBuf(uint8_t *sendBuf, int32_t length){
   if(write(fp, sendBuf, length)!=length){
      perror("I2C: Failed write to the device\n");
      return 1;
   }
   return 0;
}

int32_t I2CDEV::i2c_Write(uint8_t value){
   uint8_t buffer[1];
   buffer[0]=value;
   if (write(fp, buffer, 1)!=1){
      perror("I2C: Failed to write to the device\n");
      return 1;
   }
   return 0;
}

uint8_t I2CDEV::i2c_Read(){
   uint8_t buffer[1];
   if(read(fp, buffer, 1)!=1){
      perror("I2C: Failed to read in the value.\n");
      return 1;
   }
   return buffer[0];
}


int32_t I2CDEV::readBuf(uint32_t length, uint8_t *ReceiveBuf){
    if(read(fp, ReceiveBuf, length)!=(int)length){
      perror("IC2: Failed to read in the full buffer.\n");
      return 1;
    }
    return 0 ;
}

void I2CDEV::i2c_Close(){
	close(fp);
	fp = -1;
}


I2CDEV::~I2CDEV() {
	if(fp!=-1) this->i2c_Close();
}

