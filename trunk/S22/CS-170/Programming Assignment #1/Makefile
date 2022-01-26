PRG=gcc0.exe

GCC=g++
GCCFLAGS=-O2 -Wall -Wextra --std=c++03 -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder

OBJECTS0=grid.cpp robot.cpp 
DRIVER0=driver.cpp

VALGRIND_OPTIONS=-q --leak-check=full

DIFF_OPTIONS=--strip-trailing-cr --ignore-trailing-space

OSTYPE := $(shell uname)
ifeq (,$(findstring CYGWIN,$(OSTYPE)))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif


gcc0:
	$(GCC) -o $(PRG) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) 
0 1 2 3 4 5 6:
	@echo "running test$@"
	./$(PRG) < plan$@.txt >studentout$@
	diff out$@ studentout$@ $(DIFF_OPTIONS) > difference$@ 2>&1
clean:
	rm -f *.exe *.o
