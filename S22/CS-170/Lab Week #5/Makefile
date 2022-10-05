PRG=gnu.exe

GCC=g++
GCCFLAGS=-O -Wall -Wextra -ansi -pedantic

OBJECTS0=Vector.cpp
DRIVER0=driver.cpp

VALGRIND_OPTIONS=-q --leak-check=full

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
msc0:
	$(MSC) /Fe$@.exe           $(DRIVER0) $(OBJECTS0) $(MSCFLAGS)
1 2 3 4 5:
	echo "running test$@"
	watchdog 100 ./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ --strip-trailing-cr > difference$@
drm1 drm2 drm3 drm4 drm5:
	@echo "running memory test $@"
	drmemory -batch -no_summary --  ./$(PRG) $(subst drm,,$@) 1>/dev/null 2>difference$@
mem1 mem2 mem3 mem4 mem5:
	@echo "running memory test $@"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
clean:
	rm -f *.exe *.tds *.o *.obj *manifest* studentout* difference*
