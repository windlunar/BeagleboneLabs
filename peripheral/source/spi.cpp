

#include "../include/spi.h"


using namespace std;

SPIDEV::SPIDEV(uint32_t spiBus, uint32_t cs_num){
    this->SPIbus = spiBus ;
    this->cs_num = cs_num ;
    stringstream str_stream ;

    //Get the path of spi device that should be at /dev/spidevX.Y
	//X : bus(代表使用 SPI0 或 SPI1) ,Y : device(代表使用 CS0 或 CS1)
    str_stream << SPIDEV_PATH << SPIbus << "." << cs_num ;

    this->path = string(str_stream.str()) ;

	//初始化 SPI
    this->SPImode = MODE3 ;
	this->SPIspeed = 1000000;
    this->bitsPerFrame = 8;
	this->SPIdelay = 0;

	//開啟 SPI
    this->openSPI() ;
}


int32_t SPIDEV::openSPI(){
	fp = open(path.c_str(), O_RDWR) ;
	if (fp < 0){
		perror("Failed to open SPI.");
		return -1;
	}
	if (setConfig() < 0) return -1;
}


void SPIDEV::closeSPI(){
	close(fp);
	fp = -1;
}



int32_t SPIDEV::setConfig(){
	if (ioctl(fp, SPI_IOC_WR_MODE, &SPImode) < 0){
		perror("Failed to set SPI mode.");
		return -1;
	}
	if (ioctl(fp, SPI_IOC_RD_MODE, &SPImode) < 0){
		perror("Failed to set SPI mode.");
		return -1;
	}


	if (ioctl(fp, SPI_IOC_WR_MAX_SPEED_HZ, &SPIspeed) < 0){
		perror("Failed to set SPI speed.");
		return -1;
	}
	if (ioctl(fp, SPI_IOC_RD_MAX_SPEED_HZ, &SPIspeed) < 0){
		perror("Failed to set SPI speed.");
		return -1;
	}


	if (ioctl(fp, SPI_IOC_WR_BITS_PER_WORD, &bitsPerFrame) < 0){
		perror("Failed to set  SPI bits per word.");
		return -1;
	}
	if (ioctl(fp, SPI_IOC_RD_BITS_PER_WORD, &bitsPerFrame) < 0){
		perror("Failed to set SPI bits per word.");
		return -1;
	}
	return 0 ;
}


int32_t SPIDEV::PutAndGet(uint8_t *put, uint8_t *get, int32_t length){
	struct spi_ioc_transfer	comm;
	memset(&comm ,0 ,sizeof(comm));

	comm.tx_buf = (unsigned long) put;
	comm.rx_buf = (unsigned long) get;
	comm.len = length;
	comm.speed_hz = SPIspeed;
	comm.bits_per_word = bitsPerFrame;
	comm.delay_usecs = SPIdelay;
    comm.tx_nbits = 0;        
    comm.rx_nbits = 0;        
    comm.cs_change = 0;       
    comm.pad = 0;    

	int32_t ioctl_rtn = ioctl(fp, SPI_IOC_MESSAGE(1), &comm);
	if (ioctl_rtn < 0) {
		perror("SPI_IOC_MESSAGE Failed");
		return -1;
	}
	return ioctl_rtn;
}

