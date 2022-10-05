
GCC=g++
GCCFLAGS=-O2 -Wall -Wextra -ansi -pedantic -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder

OBJECTS0=
DRIVER0=driver.cpp
DRIVER_DNC1=driver-no-comp-1.cpp
DRIVER_DNC2=driver-no-comp-2.cpp

VALGRIND_OPTIONS=-q --leak-check=full

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),$(filter $(OSTYPE),Linux Darwin))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
dnc1:	# this target should NOT compile
	$(GCC) $(DRIVER_DNC1) -o /dev/null
dnc2:	# this target should NOT compile
	$(GCC) $(DRIVER_DNC2) -o /dev/null
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 :
	@echo "running test$@"
	watchdog 100 ./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ --strip-trailing-cr > difference$@
mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7 mem8 mem9 mem10 mem11 mem12 mem13 mem14:
	@echo "running memory test $@"
	watchdog 500 valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
drm1 drm2 drm3 drm4 drm5 drm6 drm7 drm8 drm9 drm10 drm11 drm12 drm13 drm14 :
	@echo "running memory test $@"
	drmemory -batch -no_summary --  ./$(PRG) $(subst drm,,$@) 1>/dev/null 2>difference$@
clean:
	rm -f *.exe *.tds *.o *.obj *manifest* studentout* diff*
