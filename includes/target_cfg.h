#ifndef XE_TARGET_CFG_H
#define XE_TARGET_CFG_H
// Defs

#define DBG_NULL	0
#define DBG_E9		1
#define DBG_SERIAL	2
#define DBG_VGA		4

#ifndef TARGET
#  error "Must set a target in config.h"
#elif TARGET == TARGET_NATIVE
#  define DEBUG_OUT	DBG_VGA
#elif TARGET == TARGET_BOCHS
#  define DEBUG_OUT	DBG_E9
#elif TARGET == TARGET_QEMU
#  define DEBUG_OUT	DBG_SERIAL
#else
#  error "Invalid target in config.h"
#endif

#endif // include guard
