#include <ctools.h>
#include <video.h>
#include <kalloc.h>
#include <pci.h>
//#define VMMMMEM_C(x,y)  (vmem+(((y)*80+(x))*2))
volatile unsigned char* vmem;
void panic();
void init_vga();
void disp_char(char val);
int pft();
void powerdown() __attribute__((noreturn));
extern struct {
	unsigned int low;
	unsigned int high;
} cpu_freq;

static void dbgb (char t) __attribute__ ((unused));
static void dbgb (char t) {
	if ((t >> 4) < 0x0a)
		dbg((t >> 4) + '0');
	else
		dbg((t >> 4) + 'a' - 10);

	if ((t & 0x0f) < 0x0a)
		dbg((t & 0x0f) + '0');
	else
		dbg((t & 0x0f) + 'a' - 10);
	
}
void do_multiboot(void* mbd);
void read_test();

int useDebug;
void k_main(void* mbd, unsigned int magic ) {
	useDebug = 1;
	init_con();
	for (initfn *fn = &_init_start; fn != &_init_end; fn++) {
		(*fn)();
	}
	pci_bind_drivers();
	printf("fff\nc");
//	spin(4000000000);
	do_multiboot (mbd);
	init_serial();
	//read_test();
	vmem = (unsigned char*)0xB8000;
	//Multiboot crap.
	//CON.cls(&CON);
	printf("test");
	//k_cls();
	if (magic != 0x2BADB002) { /* not multiboot! */ k_swrite("\e[1;44;37mI'm a multiboot kernel, dammit! Use a multiboot bootloader!", OUT_STD); panic(); }
//	init_vga();
	//k_s_char('a');
	printf ("Clock speed: %d\n", cpu_freq.low); //(int)cpf, (int)(1000*(cpf-(int)cpf)));
	//
	/*
	char u;
	while ((u=read_serial())) {
	    switch (u) {
		case 'b':
		case 0x7f:
			write_serial('\b');
			write_serial(' ');
			write_serial('\b');
			break;
		case '\x0d':
			write_serial(0x0d);
			write_serial(0x0a);
			break;
		case 0x03:
			powerdown();
			break;
		default:
			write_serial(u);
	    }
	}
	*/
//	for (int i = 0; i < 80*25*2; i+= 2) {
//		vmem[i+1] = (unsigned char)0x20;
//		vmem[i] = 'A';
//		//spin(100);
//	}
	
	//scroll (5);
	//spin(10000000);
	return;	
#if 0
	char *hex = "0123456789ABCDEF";
	for (int i = 0; i < 16; i++) {
		VMEM_C(1,i+3)[0] = hex[i];
		VMEM_C(i+3,1)[0] = hex[i];
	}
	VMEM_C(2,2)[0]=0xCE;
	VMEM_C(2,1)[0]=0xBA;
	VMEM_C(1,2)[0]=0xCD;
	VMEM_C(0,0)[0]=0xC9;
	VMEM_C(0,1)[0]=0xBA;
	VMEM_C(1,0)[0]=0xCD;
	VMEM_C(2,0)[0]=0xCB;
	VMEM_C(0,2)[0]=0xCC;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			VMEM_C(i+3,j+3)[0]=((j<<4) | i);
		}
	}
	//VMEM(0,1)='0';
	//MEM(0,2)='1';
	//VMEM(0,3)
#endif
}

