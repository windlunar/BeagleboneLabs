
#include "../include/uart.h"

using namespace std ;

UART::UART(int uartdev){
   stringstream ss ;
   ss << UART_PATH << uartdev ;
   devpath = ss.str() ;

   this->fd = uartOpen() ;
}


void UART::uartClose(){
   close(fd);
   fd = -1 ;
}

int UART::uartOpen(){
   if ((fd = open(devpath.c_str(), O_RDWR | O_NOCTTY))<0){
      perror("Failed to open the UART device.\n");
      return -1;
   }
   /** 
    * 控制UART各種設定的結構體 termios ,在此宣告一個termios型態的結構變數 options
    * 定義於 /usr/arm-linux-gnueabihf/include/asm-generic/termbits.h
    * 
    * tcgetattr :獲取目前的設定
    * tcsetattr :設置調整好的結構 options ,TCSANOW 代表將設定值立即改變
    * tcflush :清空緩衝區
    * 
    * B9600 : Baudrate為9600
    * CS8 : 8 bit characters
    * CREAD : 允許讀取data
    * CLOCAL :忽略控制訊號
    * IGNPAR ：忽略 parity errors
    * 
    * ICANON ：啟動正規或非正規模式(在此為非正規)(正規模式一次讀取一行,看到new line char停止)
    *
    * VMIN = 0, VTIME = 0 : 立即讀取, 若沒有讀到字元則回傳0
    * VMIN = 0, VTIME = >0 : read讀取時會在VTIME時間內等待有無data, 若沒有則回傳0
    * VMIN = >0, VTIME = 0 : read讀取時會等待資料,然後才讀取
    * VMIN = >0, VTIME = >0 : combine上面兩種
    */ 
   struct termios options;
   tcgetattr(fd, &options);
   options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;

   //options.c_cflag |= ~PARENB;     //no parity
   //options.c_cflag |= ~CSTOPB;     //not 2 stop bit

   options.c_iflag = IGNPAR /*| IGNCR*/ ;
   options.c_lflag &= ~(ICANON | ECHO | ECHOE | IEXTEN) ;
   options.c_oflag &= ~OPOST;
   options.c_cc[VMIN] = 1;
   //options.c_cc[VMIN] = 0;
   options.c_cc[VTIME] = 0;   
   tcflush(fd, TCIFLUSH);
   tcsetattr(fd, TCSANOW, &options);

   return fd ;
}

int UART::uartWrite(const char *writeBuf, int len){
   int cnt;
   if ((cnt = write(fd, writeBuf, len))<0){
      perror("Failed to write to the UART device.\n");
      return -1;
   }
   return cnt ;
}

int UART::uartRead(char *readBuf, int len){
   int cnt;
   if ((cnt = read(fd, readBuf, len))<0){
      perror("Failed to Read to the UART device.\n");
      return -1;
   }
   return cnt ;
}

int UART::putChar(char ch){
   int cnt;
   char buf[1] ;
   buf[0] = ch ;
   if ((cnt = write(fd, buf, 1))<0){
      perror("Failed to write to the UART device.\n");
      return -1;
   }
   return cnt ;
}

int UART::getChar(char *readBuf){
   int cnt;
   if ((cnt = read(fd, readBuf, 1))<0){
      perror("Failed to Read to the UART device.\n");
      return -1;
   }
   return cnt ;
}


UART::~UART(){
   uartClose() ;
   
}



void printProgress(int count, unsigned long filesize){
    float percent = (float)count / filesize ;

    cout << "Progress: " << fixed << setprecision(2) << 100*percent 
		 << " %" << "     \r" << flush;
}