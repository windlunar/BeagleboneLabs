
#ifndef __I2C_H_
#define __I2C_H_

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>

#include <iostream>
#include <sstream>
#include <cstdio>

#define I2C_PATH "/dev/i2c-"


class I2CDEV{
private:
	uint32_t bus;
	uint32_t i2cAddr;
	int32_t fp;

public:
	I2CDEV(uint32_t bus, uint32_t i2cAddr);
	int32_t i2c_Open();

	int32_t i2c_Write(uint8_t value);
	uint8_t i2c_Read();

	int32_t writeBuf(uint8_t *sendBuf, int32_t length);
	int32_t readBuf(uint32_t length, uint8_t *ReceiveBuf);

	void i2c_Close();
	~I2CDEV();
};


#endif 
