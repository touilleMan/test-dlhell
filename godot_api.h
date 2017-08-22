#ifndef GODOT_API_H_
#define GODOT_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WINDOWS

#ifdef MODULE
#define GDAPI __declspec(dllimport)
#else
#define GDAPI __declspec(dllexport)
#endif

#else

#define GDAPI

#endif

GDAPI extern const char *godot_hello(int x);

#ifdef __cplusplus
}
#endif

#endif
