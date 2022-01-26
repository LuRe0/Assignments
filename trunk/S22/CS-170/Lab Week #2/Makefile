PRG=gnu.exe
GCC=g++
GCCFLAGS=-Wall -Wextra -ansi -pedantic -g -O2 -Werror
LFLAGS=

OBJECTS0=fibonacci.cpp
DRIVER0=main.cpp

VALGRIND_OPTIONS=-q --leak-check=full --show-reachable=yes --tool=memcheck --suppressions=/home/mmead/bin/false-8.supp
DIFF_OPTIONS=-y -W220 --strip-trailing-cr --suppress-common-lines -b

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

clang0:
	clang++ -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(LFLAGS)
gcc0:
	g++ -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(LFLAGS)
0:
	echo "running test$@"
	@echo "should run in less than 200 ms"

	/home/mmead/bin/dos2unix --keepdate $(OBJECTS0)
	/home/mmead/bin/tablen $(OBJECTS0) -v >studentout$@
	/home/mmead/bin/wd 4000 4000 valgrind $(VALGRIND_OPTIONS) ./$(PRG) 12 | /home/mmead/bin/throttle 1000 -we >>studentout$@
	/home/mmead/bin/wd 4000 4000 valgrind $(VALGRIND_OPTIONS) ./$(PRG) 46 | /home/mmead/bin/throttle 2500 -we >>studentout$@
	@echo "lines after the next are mismatches with master output -- see out$@"
	diff output$@.txt studentout$@ $(DIFF_OPTIONS)
	( cat Doxyfile ; echo "EXTRACT_ALL=YES" ) | doxygen - 2>>difference$@
	( cat Doxyfile ; echo "EXTRACT_ALL=NO" ) | doxygen - 2>>difference$@
	/home/mmead/bin/checkdox-lab03.sh >>difference$@
clean : 
	rm *.exe student* difference*
