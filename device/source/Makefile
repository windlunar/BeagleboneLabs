


include ../../common.make

obj_destination_path = ../../build/object
obj=adxl345_I2C.o adxl345_SPI.o us100_ultrasonic.o

.PHONY : all
all: $(obj) copy
	
%.o : %.$(source)
	$(toolchain) -c $^ -o $@

.PHONY : copy
copy:
	cp *.o $(obj_destination_path)
	rm -rf *.o
































