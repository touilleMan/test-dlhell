#include <iostream>

#if WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "godot_api.h"


static int return_value = 0;


const char *godot_hello(int x) {
	return_value = x;
	static const char hello[] = "Hello world !";
	return hello;
}


int main() {
	// Build the API struct
	const godot_api_t api = {
#ifdef WINDOWS
		.godot_hello=godot_hello
#else
		// Nothing to do
#endif
	};

#if WINDOWS
	HINSTANCE handle = LoadLibrary("libmodule.dll");
	if (!handle) {
		std::cout << "handle is NULL: " << std::endl;
		return -1;
	}
	FARPROC bootstrap = GetProcAddress(handle, "bootstrap");
	if (!bootstrap) {
		std::cout << "bootstrap is NULL: " << std::endl;
		return -1;
	}
	((void (*)(const godot_api_t*))bootstrap)(&api);

#else

	// Load the module and call it bootstrap function
	void *handle = dlopen("./libmodule.so", RTLD_NOW | RTLD_GLOBAL);
	if (!handle) {
		std::cout << "handle is NULL: " << dlerror() << std::endl;
		return -1;
	}
	void *bootstrap = dlsym(handle, "bootstrap");
	if (!bootstrap) {
		std::cout << "bootstrap is NULL: " << dlerror() << std::endl;
		return -1;
	}
	((void (*)(const godot_api_t*))bootstrap)(&api);
#endif

	return return_value;
}
