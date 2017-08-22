#ifndef GODOT_API_H_
#define GODOT_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WINDOWS

// Mega struct full of function pointers
typedef struct {
    const char *(*godot_hello)(int x);
} godot_api_t;

#define GODOT_API_ANCHOR() static godot_api_t *__GODOT_API_ANCHOR__
#define GODOT_API_BOOTSTRAP(api) __GODOT_API_ANCHOR__ = api


#ifdef MODULE
#define GDAPI __declspec(dllimport)

// one macro per function in the api
// #define godot_hello(x) __GODOT_API_ANCHOR__->godot_hello(x)
// Or we could provide the functions with wrapper functions to avoid macro hell
static const godot_api_t *__GODOT_API_ANCHOR__;
static inline const char *godot_hello(int x) { return __GODOT_API_ANCHOR__->godot_hello(x); }

#else
#define GDAPI __declspec(dllexport)
#endif



// ...

#else // Not WINDOWS

#define GDAPI

// None of this madness is needed, provide empty macros
#define GODOT_API_ANCHOR()
#define GODOT_API_BOOTSTRAP(api)
typedef struct {
    void *dummy;
} godot_api_t;

GDAPI extern const char *godot_hello(int x);  // godot_hello is a real function here

#endif


#ifdef __cplusplus
}
#endif

#endif
