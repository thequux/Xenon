#include <ctools.h>
#ifndef XE_DRIVER_H
#define XE_DRIVER_H

/// Yuck. Will fix this braindamage ASAP.
#define DRV(contents) union {char __fill[128]; struct { contents }; }


// The wad of registers passed to a driver... I'm sure this interface
// will change, and I'm hoping that I can get rid of this ASAP. 
struct regs {
	int eax;
	int ebx;
	int ecx;
	int edx;
};
struct driver_base {
	int (*init)(char* cmd); // Called by kernel at boot.
	int (*destroy)();	// called by kernel at shutdown.
	int (*dispatch)(int cmd, int minor, struct regs*);
				// Call to driver. Kernel mode stuff may use
				// driver-type specific calls (like scroll)
				// rather than using a dispatch, but this is 
				// probably more flexible for user->sys calls.
				// That doesn't change the fact that its UGLEE
				// \param cmd The syscall number
				// \param minor The device minor number.
				// \param regs The registers on entry into the
				// 	       interrupt. DO NOT CHANGE!!!
				// \return Whatever the syscall should return
	void *base;		// Base address of module. May be removed
	int id;	// an opaque, unique ID. Set by kernel before init is called
	int type;		// Filled by driver on init; specfies type
				// of device controlled.
};

struct driver {
	DRV(
	struct driver_base base;
	);
};

struct console;
struct console_driver {
	DRV(
	struct driver_base base;
	BOOL (*allocateConsole)(struct console* con);
	BOOL (*destroyConsole)(struct console* con);
	);
};
#endif
