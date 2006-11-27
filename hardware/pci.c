#include <ctools.h>
#include <video.h>
struct pci_dev {
	int bus;
	int slot;
	int fn;
	int vendor;
	int device;
};

struct pci_dev pci_devs[128];
int devCount;

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

unsigned short pciConfigReadWord (unsigned short bus, unsigned short slot,
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
   tmp = (unsigned short)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   return (tmp);
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
   printf ("\e[1;32mPCI Address Space\e[0m\n"
           "%s\n"
           "\xba""bus :slot.fn    VEND:DEVID\xba\n", buf);
   for (int i=1; i < 27; i++) buf[i] = 0xc4;
   buf[0]=0xc7;
   buf[27]=0xb6;
   printf ("%s\n", buf);
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
		d->fn = fn;
		d->vendor = vendor;
		d->device = device;
	    	if ((headerType & 0x7f) == 2) {
	    	    int mb2 = pciConfigReadWord(bus,slot,fn,0x1a) & 0xff;
	    	    if (mb2 > max_bus) max_bus = mb2;
		}

//		printf ("\xba%04hx:%04hx.%1d     %04hx:%04hx \xba\n",
//                         bus, slot, fn, vendor, device);
	     }
         }
      }
   }

   for (int i = 0; i < devCount; i+= 4) {
   	for (int j = i; j<i+4 && j<devCount; j++) {
		printf ("%02x:%02x.%1x %04x:%04x%s", 
			pci_devs[j].bus,
			pci_devs[j].slot,
			pci_devs[j].fn,
			pci_devs[j].vendor,
			pci_devs[j].device,
			((j != i+3)?" \xba ":""));
	}
	printf ("\n");
   }
   	// bb.dd.f  vend:devi |
   //for (int i=1; i < 27; i++) buf[i] = 0xcd;
   //buf[0]=0xc8;
   //buf[27] = 0xbc;
  // printf ("%s\n", buf);
}

