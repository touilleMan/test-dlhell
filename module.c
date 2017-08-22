#include <stdio.h>

#include "godot_api.h"


void bootstrap(const godot_api_t *api) {
	GODOT_API_BOOTSTRAP(api);
	const char *hello = godot_hello(0);
	printf("%s\n", hello);
}
