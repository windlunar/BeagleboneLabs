

include common.make

obj_destination_path=./build/object
bin_destination_path=./build

root_dir = $(shell pwd)

#Build
.PHONY : all
all:
	mkdir -p build
	make -C ./peripheral
	make -C ./device
	make -C ./main
	make -C ./build/object

	@echo
	@echo Build sucessfully!

#Clean objects and bin
.PHONY : clean
clean :
	-rm $(bin_destination_path)/*.elf
	-rm $(obj_destination_path)/*.o
	

.PHONY : uploadex
uploadex :
	scp ./build/lab* ubuntu@192.168.6.2:/home/ubuntu











