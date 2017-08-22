#include <iostream>

#if WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "godot_api.h"


static int return_value = -1;

#ifdef __cplusplus
extern "C" {
#endif


const char *godot_hello(int x) {
	return_value = x;
	static const char hello[] = "Hello world !";
	return hello;
}


#ifdef __cplusplus
}
#endif


int main() {
	// Build the API struct
#if WINDOWS
	HINSTANCE handle = LoadLibraryEx("libmodule.dll", NULL, LOAD_IGNORE_CODE_AUTHZ_LEVEL);
	if (!handle) {
		std::cout << "handle is NULL: " << GetLastError() << std::endl;
		return -1;
	}
	FARPROC bootstrap = GetProcAddress(handle, "bootstrap");
	if (!bootstrap) {
		std::cout << "bootstrap is NULL: " << GetLastError() << std::endl;
		return -1;
	}
	((void (*)())bootstrap)();

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
	((void (*)())bootstrap)();
#endif

	return return_value;
}
