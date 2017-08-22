#include <stdio.h>

#include "godot_api.h"


void bootstrap() {
	const char *hello = godot_hello(0);
	printf("%s\n", hello);
}
