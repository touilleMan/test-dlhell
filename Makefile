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
CFLAGS+=-DWINDOWS
LINKFLAGS=
else
CFLAGS=
LINKFLAGS=-ldl
endif

ifeq ($DEBUG,yes)
CFLAGS+=-g -ggdb
endif

all: godot module
	./godot

debug: godot module
	lldb ./godot


godot: godot_main.cpp godot_api.h
	$(CXX) godot_main.cpp -o $(GODOT) $(CFLAGS) $(LINKFLAGS)


module: libmodule.so godot_api.h
	# does nothing more


module.o: module.c
	$(CC) -c -Wall -Werror -fpic module.c $(CFLAGS)


libmodule.so: module.o
	$(CC) --shared module.o -o $(MODULE)


clean:
	rm -f module.o libmodule.so godot godot.exe
