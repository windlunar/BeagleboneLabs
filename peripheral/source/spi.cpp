

#include "../include/spi.h"


using namespace std;

SPIDEV::SPIDEV(uint32_t spiBus, uint32_t spiDevice){
    this->bus = spiBus ;
    this->device = spiDevice ;
    stringstream str_stream ;

    //Get the path of spi device that should be at /dev/spidevX.Y
	//X : bus(代表使用 SPI0 或 SPI1) ,Y : device(代表使用 CS0 或 CS1)
    str_stream << SPIDEV_PATH << bus << "." << device ;

    this->path = string(str_stream.str()) ;

	//初始化 SPI
    this->mode = MODE3 ;
    this->bitsPerFrame = 8;
	this->speed = 500000;
	this->delay = 0;

	//開啟 SPI
    this->openSPI() ;
}


int32_t SPIDEV::openSPI(){
	if ((fp = open(path.c_str(), O_RDWR))<0){
		perror("SPI: Can't open device.");
		return -1;
	}
	if (this->setMode(this->mode)==-1) return -1;
	if (this->setSpeed(this->speed)==-1) return -1;
	if (this->setBitsPerWord(this->bitsPerFrame)==-1) return -1;
}


void SPIDEV::closeSPI(){
	close(fp);
	fp = -1;
}


int32_t SPIDEV::setBitsPerWord(uint8_t bits){
	this->bitsPerFrame = bits;
	if (ioctl(this->fp, SPI_IOC_WR_BITS_PER_WORD, &this->bitsPerFrame)==-1){
		perror("Error: Can't set bits per word.");
		return -1;
	}
	if (ioctl(this->fp, SPI_IOC_RD_BITS_PER_WORD, &this->bitsPerFrame)==-1){
		perror("Error: Can't get bits per word.");
		return -1;
	}
	return 0;
}


int32_t SPIDEV::setSpeed(uint32_t speed){
	this->speed = speed;
	if (ioctl(this->fp, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed)==-1){
		perror("Error: Can't set transfer speed.");
		return -1;
	}
	if (ioctl(this->fp, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed)==-1){
		perror("Error: Can't get transfer speed.");
		return -1;
	}
	return 0;
}


int32_t SPIDEV::setMode(int32_t mode){
	this->mode = mode;
	if (ioctl(this->fp, SPI_IOC_WR_MODE, &this->mode)==-1){
		perror("Error: Can't set SPI mode.");
		return -1;
	}
	if (ioctl(this->fp, SPI_IOC_RD_MODE, &this->mode)==-1){
		perror("Error: Can't get SPI mode.");
		return -1;
	}
	return 0;
}


int32_t SPIDEV::PutAndGet(uint8_t *put, uint8_t *get, int32_t length){
	struct spi_ioc_transfer	transfer;
	memset(&transfer,0,sizeof(transfer));
	transfer.tx_buf = (unsigned long) put;
	transfer.rx_buf = (unsigned long) get;
	transfer.len = length;
	transfer.speed_hz = this->speed;
	transfer.bits_per_word = this->bitsPerFrame;
	transfer.delay_usecs = this->delay;
    transfer.tx_nbits = 0;        
    transfer.rx_nbits = 0;        
    transfer.cs_change = 0;       
    transfer.pad = 0;             
	int status = ioctl(fp, SPI_IOC_MESSAGE(1), &transfer);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE Failed");
		return -1;
	}
	return status;
}

