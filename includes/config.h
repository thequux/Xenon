#ifndef XE_CONFIG_H
#define XE_CONFIG_H
// Various target-specific features, such as debug ports, etc.
#define TARGET_NATIVE	0
#define TARGET_BOCHS	1
#define TARGET_QEMU	2

#define TARGET	TARGET_QEMU

#include <target_cfg.h>

//Overrides...

// Where should I send debug output? DBG_E9 is for bochs only (AFAIK),
// serial is good for nearly anything, and null disables debug output
//
// Techincal details:
// DBG_E9 sends debugging stuff to hardware port E9
// DBG_SERIAL uses ttyS0 (or COM1)
// DBG_NULL turns dbg into a NOP
//
// #define DEBUG_OUT DBG_NULL
#endif
