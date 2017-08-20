#include <stdio.h>

#include "godot_api.h"


// GODOT_API_ANCHOR();


void bootstrap(const godot_api_t *api) {
	GODOT_API_BOOTSTRAP(api);
	const char *hello = godot_hello(42);
	printf("%s\n", hello);
}
