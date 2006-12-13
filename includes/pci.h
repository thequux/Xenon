#include <types.h>
struct BAR {
	void* base;
	u32_t length;
	BOOL mmio;
	char type;
	BOOL prefetch;
};
struct pci_dev {
	u16_t vendor;
	u16_t device;
	u16_t subsys;
	
	u8_t dclass;
	u8_t subclass;
	
	u8_t bus;
	u8_t slot;
	u8_t func;

	struct BAR bar[8];

	BOOL claimed;	// if a driver has claimed the device
} pci_devs[128];

typedef void (*pci_dev_init)(struct pci_dev* device);
struct pci_driver {
	u16_t vendor;
	u16_t device;
	pci_dev_init init;
};


void pciScanBus();
u8_t  pciConfigReadByte (unsigned short bus, unsigned short slot,
			 unsigned short func, unsigned short offset);
u16_t pciConfigReadWord (unsigned short bus, unsigned short slot,
			 unsigned short func, unsigned short offset);
u32_t pciConfigReadDWord (unsigned short bus, unsigned short slot,
			 unsigned short func, unsigned short offset);

void register_pci_driver (struct pci_driver *driver);
void pci_bind_drivers();
