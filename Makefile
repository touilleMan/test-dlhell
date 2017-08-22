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
LINKFLAGS=-rdynamic
else
CFLAGS=-Wall -Werror
LINKFLAGS=-ldl -rdynamic
endif

ifeq ($DEBUG,yes)
CFLAGS+=-g -ggdb
endif

all: godot module
	./godot

debug: godot module
	lldb ./godot


godot_main.o: godot_main.cpp godot_api.h
	$(CXX) -c -fPIC godot_main.cpp $(CFLAGS)


godot: godot_main.o
	$(CXX) godot_main.o -o $(GODOT) $(CFLAGS) $(LINKFLAGS)


module: libmodule.so godot_api.h
	# does nothing more


module.o: module.c
	$(CC) -c -fPIC module.c $(CFLAGS)


libmodule.so: module.o
	$(CC) --shared module.o -o $(MODULE)


clean:
	rm -f *.o godot godot.exe
