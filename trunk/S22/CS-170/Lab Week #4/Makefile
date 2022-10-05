PRG=gcc0.exe

GCC=g++
GCCFLAGS=-O2 -Wall -Wextra -ansi -pedantic -g

OBJECTS0=List.cpp
DRIVER0=main.cpp

VALGRIND_OPTIONS=-q --leak-check=full

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) 
0 1 2 3 4 5 6 7:
	echo "running test_$@"
	./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ --strip-trailing-cr > difference$@
mem0 mem1 mem2 mem3 mem4 mem5 mem6:
	@echo "running memory test $@"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
drm0 drm1 drm2 drm3 drm4 drm5 drm6:
	@echo "running memory test $@"
	drmemory -batch -no_summary -- ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
all:
	make 0 1 2 3 4 5 6 mem0 mem1 mem2 mem3 mem4 mem5 mem6
clean:
	rm -f *.exe *.tds *.o *.obj *manifest* studentout* difference*
