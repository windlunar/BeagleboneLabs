


include ../../common.make

obj_destination_path = ../../build/object
obj=adxl345_I2C.o adxl345_SPI.o us100_ultrasonic.o mpu6050_i2c.o L9110S.o

.PHONY : all
all: $(obj) copy
	
%.o : %.$(source)
	$(toolchain) -c $^ -o $@

.PHONY : copy
copy:
	cp *.o $(obj_destination_path)
	rm -rf *.o
































