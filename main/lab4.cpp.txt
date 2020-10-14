
#include <iostream>
#include <unistd.h>

#include "../device/include/adxl345_I2C.h"
#include "../peripheral/include/i2c.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Start the test to get acceleration from ADXL345." << endl;
	if( argc != 2 ){
		cout << "Error : Wrong argument number" << endl ;
		cout << "Please type the command like './i2c_XYZ.elf 2'" << endl ;
		return -1 ;
	}

	I2CDEV i2cdev(stoi(argv[1]), 0x53) ;
	ADXL345_I2C adxl345(&i2cdev);

	printf("ID of ADLX345 : 0x %x\n\n",adxl345.readReg(0x00));

	//Get x y z三方向的加速度並印出來
	adxl345.print_AccelXYZ(200) ;

	i2cdev.i2c_Close() ;

	cout << "\n\n" << "Test Complete." << endl;
	return 0 ;
}
