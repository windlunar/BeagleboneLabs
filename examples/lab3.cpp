#include <iostream>

#include "../device/include/adxl345_SPI.h"
#include "../peripheral/include/spi.h"

using namespace std;

int main(int argc, char *argv[]){
   cout << "Start the test to get acceleration from ADXL345." << endl;
   if( argc != 3 ){
      perror("Error : Wrong arg number") ;
      return -1 ;
   }
   //建立 SPI物件
   SPIDEV spidev(stoi(argv[1]),stoi(argv[2]));
   //建立 adxl345物件
   ADXL345_SPI adxl345(&spidev); 

   printf("ID of ADLX345 : 0x %x\n\n",adxl345.readReg(0x00));

   //Get x y z三方向的加速度並印出來
   adxl345.print_AccelXYZ(200) ;

   spidev.closeSPI() ;

   cout << "\n\n" << "Test Complete." << endl;
   return 0 ;
}
