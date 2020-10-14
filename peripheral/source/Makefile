


include ../../common.make

obj_destination_path = ../../build/object
obj=i2c.o pwm.o spi.o uart.o

.PHONY : all
all: $(obj) copy
	
%.o : %.$(source)
	$(toolchain) -c $^ -o $@

.PHONY : copy
copy:
	cp *.o $(obj_destination_path)
	rm -rf *.o
































