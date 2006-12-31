#include <ctools.h>
#include <types.h>
#include <video.h>
uchar in_buf[512];

#define f00(x)
#define BMASK(hi,lo) ((2<<(hi))-(1<<(lo)))
#define SEL(n,sp)	 n?sp  
#define BIT(spec)	 BMASK(SEL(1,spec),SEL(0,spec))
#define BSEL(val,spec)	(((val) & BIT(spec))>>(SEL(0,spec)))
void disk_read(int sector, uchar *buf) {
	outb (0x1f6, 0xa0 | BSEL(sector,27:24));
	outb (0x1f2, 0x02);
	outb (0x1f3, BSEL(sector, 7:0 ));
	outb (0x1f4, BSEL(sector, 15:8));
	outb (0x1f4, BSEL(sector, 23:16));
	outb (0x1f7, 0x20);
	while (!(inb(0x1f7) & 0x08))
		; // wait.
	u32_t *b2 = (u32_t*)buf;
	for (int i = 0; i < 512/4; i+=1)
		b2[i] = inl(0x1f0);
}

void read_test() {
	// Generate a checksum of the boot sector, and output it.
	disk_read (1, in_buf);
	uchar cks = 0;
	for (int i = 0; i < 512; i++)
		cks += in_buf[i];
	printf ("Bootloader checksum: %02x\n", (u32_t)cks);
}


