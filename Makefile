
all: compile

configure:
	(if [ ! -x build ] ; then mkdir build ; fi)
	(cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..)
	
compile:
	make -C build
	
run:
	(./build/bin/light_pre_pass)
	
debug:
	(gdb --args ./build/bin/light_pre_pass)
	
test:
	(cd build/bin && ./unit_test)
	
clean:
	make -C build clean
	
distclean:
	(rm -rf build)