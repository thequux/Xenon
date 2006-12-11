#include <ctools.h>
#include <video.h>
#include <pci.h>
/*struct pci_dev {
	int bus;
	int slot;
	int fn;
	int vendor;
	int device;
};*/

struct pci_dev pci_devs[128];
int devCount;
struct pci_driver *drivers[128];
int drv_count;
inline unsigned long pciAddress (unsigned short bus, unsigned short slot,
			  unsigned short func, unsigned short offset) {
	return (unsigned long)(
		(((unsigned long)(bus )) << 16) |
		(((unsigned long)(slot)) << 11) |
		(((unsigned long)(func)) << 8 ) |
		(offset                && 0xfc) |
		((unsigned int )0x80000000)
		);
}

u8_t pciConfigReadByte (unsigned short bus, unsigned short slot,
                                  unsigned short func, unsigned short offset)
{
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;
   unsigned short tmp = 0;

   /* create configuration address as per Figure 1 */
   address = (unsigned long)((lbus << 16) | (lslot << 11) |
           (lfunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));

   /* write out the address */
   outl (0xCF8, address);
   /* read in the data */
   tmp = (u8_t)((inl (0xCFC) >> ((offset & 3) * 8)) & 0xffff);
   return (tmp);
}
u16_t pciConfigReadWord (unsigned short bus, unsigned short slot,
                                 unsigned short func, unsigned short offset)
{
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;
   unsigned short tmp = 0;

   /* create configuration address as per Figure 1 */
   address = (unsigned long)((lbus << 16) | (lslot << 11) |
           (lfunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));

   /* write out the address */
   outl (0xCF8, address);
   /* read in the data */
   tmp = (u16_t)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   return (tmp);
}

u32_t pciConfigReadDWord (u16_t bus, u16_t slot, u16_t func, u16_t offset) {
   unsigned long address;
   unsigned long lbus = (unsigned long)bus;
   unsigned long lslot = (unsigned long)slot;
   unsigned long lfunc = (unsigned long)func;

   /* create configuration address as per Figure 1 */
   address = (unsigned long)((lbus << 16) | (lslot << 11) |
           (lfunc << 8) | (offset & 0xfc) | ((unsigned int)0x80000000));

   /* write out the address */
   outl (0xCF8, address);
   /* read in the data */
   return inl (0xCFC);
}
void pciScanBus()
{
   devCount = 0;
   int max_bus = 1;
   char buf[29];
   for (int i=1; i < 27; i++) buf[i] = 0xcd;
   buf[0]=0xc9;
   buf[27] = 0xbb;
   buf[28] = 0;
/*   printf ("\e[1;32mPCI Address Space\e[0m\n"
           "%s\n"
           "\xba""bus :slot.fn    VEND:DEVID\xba\n", buf);*/
   for (int i=1; i < 27; i++) buf[i] = 0xc4;
   buf[0]=0xc7;
   buf[27]=0xb6;
//   printf ("%s\n", buf);
   unsigned short vendor,device;
   for (unsigned short bus = 0; bus < max_bus; bus++) {

      for (unsigned short slot = 0; slot < 32; slot++) {
	    
   /* try and read the first configuration register. Since there are no */
   /* vendors that == 0xFFFF, it must be a non-existent device. */
         if ((vendor = pciConfigReadWord(bus,slot,0,0)) != 0xFFFF) {
            device = pciConfigReadWord(bus,slot,0,2);
	    int ct = 1;

	    char headerType = pciConfigReadWord(bus,slot,0,0x0e) & 0xff ;
	    if ( headerType & 0x80)
	    	ct = 8;
	    for (int fn = 0; fn < ct; fn++) {
	    	vendor =  pciConfigReadWord(bus,slot,fn,0);
		device =  pciConfigReadWord(bus,slot,fn,2);
		if (vendor == 0xFFFF)
		    continue;
		struct pci_dev *d = pci_devs + devCount;
		devCount++;
		d->bus = bus;
		d->slot = slot;
		d->func = fn;
		d->vendor = vendor;
		d->device = device;
	    	if ((headerType & 0x7f) == 2) {
	    	    int mb2 = pciConfigReadWord(bus,slot,fn,0x1a) & 0xff;
	    	    if (mb2 > max_bus) max_bus = mb2;
		}
		u16_t cls = pciConfigReadWord (bus, slot, fn, 0x08);
		d->dclass = cls >> 8;
		d->subclass = cls & 0xff;

//		printf ("\xba%04hx:%04hx.%1d     %04hx:%04hx \xba\n",
//                         bus, slot, fn, vendor, device);
	     }
         }
      }
   }
/*
   for (int i = 0; i < devCount; i+= 4) {
   	for (int j = i; j<i+4 && j<devCount; j++) {
		printf ("%02x:%02x.%1x %04x:%04x%s", 
			pci_devs[j].bus,
			pci_devs[j].slot,
			pci_devs[j].func,
			pci_devs[j].vendor,
			pci_devs[j].device,
			((j != i+3)?" \xba ":""));
	}
	printf ("\n");
   }*/
   	// bb.dd.f  vend:devi |
   //for (int i=1; i < 27; i++) buf[i] = 0xcd;
   //buf[0]=0xc8;
   //buf[27] = 0xbc;
  // printf ("%s\n", buf);
}

void pciReadBARs (struct pci_dev *dev) {
	int i = 0;
	for (i = 0; i < 6; i++) {
		u32_t bar = pciConfigReadDWord (dev->bus, dev->slot, dev->func, 0x10+i*4);
		if (bar & 0x01) {
			dev->bar[i].mmio = TRUE;
			dev->bar[i].type=0;
			dev->bar[i].prefetch=FALSE;
			dev->bar[i].base = (void*)(bar & (~0x03));
		} else {
			dev->bar[i].mmio = FALSE;
			dev->bar[i].type = (bar>>1) & 0x03;
			dev->bar[i].prefetch = (bar & 0x08)?TRUE:FALSE;
			dev->bar[i].base = (void*)(bar & (~0x0f));
		}
	}
}

void register_pci_driver (struct pci_driver *driver) {
	drivers[drv_count++] = driver ;
}
static void pci_try_bind_device(struct pci_dev *dev) {
	for (int i = 0; i < drv_count; i++) {
		for (int j = 0; (drivers[i])[j].vendor != 0; j++) {
			if (drivers[i][j].vendor == dev->vendor &&
			    drivers[i][j].device == dev->device) {
				dev->claimed = TRUE;
				drivers[i][j].init(dev);
				return;
			}
		}
	}
}
void pci_bind_drivers() {
	pciScanBus();
	for (int i = 0; i < devCount; i++) {
		pciReadBARs(pci_devs+i);
		pci_try_bind_device(pci_devs+i);
	}
}
