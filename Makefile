ifeq ($(XCOMPILE),yes)
CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
GODOT=godot.exe
MODULE=libmodule.dll
WINDOWS=yes
else
CC?=clang
CXX?=clang++
GODOT=godot
MODULE=libmodule.so
endif

ifeq ($(WINDOWS),yes)
CFLAGS+=-DWINDOWS -Wall -Werror
LINKFLAGS=
GODOT_LINKFLAGS=$(LINKFLAGS) -Wl,--out-implib,libgodot.a
MODULE_LINKFLAGS=$(LINKFLAGS) -Wl,--out-implib,libmodule.a libgodot.a
else
CFLAGS=-Wall -Werror -fPIC
LINKFLAGS=-ldl -rdynamic
GODOT_LINKFLAGS=$(LINKFLAGS)
MODULE_LINKFLAGS=$(LINKFLAGS)
endif

ifeq ($DEBUG,yes)
CFLAGS+=-g -ggdb
endif

all: godot module
	./godot

debug: godot module
	lldb ./godot


godot_main.o: godot_main.cpp godot_api.h
	$(CXX) -c godot_main.cpp $(CFLAGS)


godot: godot_main.o
	$(CXX) godot_main.o -o $(GODOT) $(CFLAGS) $(GODOT_LINKFLAGS)


module: libmodule.so godot_api.h
	# does nothing more


module.o: module.c
	$(CC) -c module.c $(CFLAGS) -DMODULE


libmodule.so: module.o
	$(CC) --shared module.o -o $(MODULE) $(MODULE_LINKFLAGS)


clean:
	rm -f *.o *.a *.def godot godot.exe libmodule.dll
