


include ../common.make

obj_destination_path=../build/object
obj=$(main_proc_name).o

.PHONY : all
all: $(obj) copy
	
%.o : %.cpp
	arm-linux-gnueabihf-g++ -c $^ -o $@

.PHONY : copy
copy:
	cp *.o $(obj_destination_path)
	rm -rf *.o
































