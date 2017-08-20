// godot.h

#if WINDOWS

// Mega struct full of function pointers
typedef struct {
	godot_string (*godot_do_something)(godot_int x);
	...
} godot_api_t;

#define GODOT_API_ANCHOR() static godot_api_t *__GODOT_API_ANCHOR__
#define GODOT_API_BOOTSTRAP(api) __GODOT_API_ANCHOR__ = api

// one macro per function in the api
#define godot_string godot_do_something(godot_int x) __GODOT_API_ANCHOR__->godot_do_something(x)
// Or we could provide the functions with wrapper functions to avoid macro hell
static inline godot_string godot_do_something(godot_int x) { return __GODOT_API_ANCHOR__->godot_do_something(x); }

// ...

#else

// None of this madness is needed, provide empty macros
#define GODOT_API_ANCHOR()
#define GODOT_API_BOOTSTRAP(api)
typedef struct {
	void *dummy;
} godot_api_t;

godot_string godot_do_something(godot_int x);  // godot_do_something is a real function here
// ...

#endif


// my_module.c

GODOT_API_ANCHOR();  // must be defined once


void call_by_godot_on_library_load(const godot_api_t *api) {
	GODOT_API_BOOTSTRAP(api); // should be call once
	godot_string foo;
	godot_string_new(&foo);
	// etc...
}
