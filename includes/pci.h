struct BAR {
	void* base;
	u32_t length;
};
struct pci_dev {
	u16_t vendor;
	u16_t device;
	u16_t subsys;
	u16_t devclass;
	
	u8_t bus;
	u8_t slot;
	u8_t func;

	struct BAR bar[8];

	BOOL claimed;	// if a driver has claimed the device
} pci_devs[128];

void pciScanBus();
u8_t  pciConfigReadByte (unsigned short bus, unsigned short slot,
			 unsigned short func, unsigned short offset);
u16_t pciConfigReadWord (unsigned short bus, unsigned short slot,
			 unsigned short func, unsigned short offset);


