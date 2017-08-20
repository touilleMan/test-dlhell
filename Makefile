ifeq ($(WINDOWS),yes)
CFLAGS+=-DWINDOWS
else
CFLAGS=
endif

all: godot module
	./godot

debug: godot module
	lldb ./godot


godot: godot_main.cpp godot_api.h
	clang++ godot_main.cpp -ldl -g -ggdb -o godot $(CFLAGS)


module: libmodule.so godot_api.h
	# does nothing more


module.o: module.c
	clang -c -Wall -Werror -fpic -g -ggdb module.c $(CFLAGS)


libmodule.so: module.o
	clang --shared module.o -o libmodule.so


clean:
	rm -f module.o libmodule.so godot
