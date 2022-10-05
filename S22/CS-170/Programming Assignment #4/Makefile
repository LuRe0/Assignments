PRG=gcc0.exe

GCC=g++
GCCFLAGS=-Wall -Wextra -ansi -pedantic -O2 -Wconversion -g

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines

OBJECTS0=table.cpp
DRIVER0=driver.cpp
DRIVER1=driver.cc.1.cpp
DRIVER2=driver.cc.2.cpp

OSTYPE := $(shell uname)
#ifeq ($(OSTYPE),Linux)
ifeq ($(OSTYPE),$(filter $(OSTYPE),Linux Darwin))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
gcc_cc1:
	$(GCC) -o $@.exe $(CYGWIN) $(DRIVER1) $(OBJECTS0) $(GCCFLAGS)
gcc_cc2:
	$(GCC) -o $@.exe $(CYGWIN) $(DRIVER2) $(OBJECTS0) $(GCCFLAGS)
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24:
	@echo "running test$@"
	./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ --strip-trailing-cr > difference$@
mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7 mem8 mem9 mem10 mem11 mem12 mem13 mem14 mem15 mem16 mem17 mem18 mem19 mem20 mem21 mem22 mem23 mem24:
	@echo "running memory test $@"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
clean:
	rm -f *.o *.obj
