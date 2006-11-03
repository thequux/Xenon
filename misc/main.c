#include "ctools.h"
#include "video.h"
//#define VMMMMEM_C(x,y)  (vmem+(((y)*80+(x))*2))
volatile unsigned char* vmem;
void panic();
int pft();
struct __attribute__ ((packed)) mb_mod {
	void *start;
	void *end;
	char *module_id; // this is up to me...
	int reserved;

};
struct __attribute__ ((packed)) mboot_info {
	int flags;
	struct { // memory info... if flags[0]
		int mem_lower;
		int mem_upper;
	} mem_info;
	struct { // boot device... if flags[1]
		char drive;
		char part1;
		char part2;
		char part3;
	} boot_info;
	char* cmdline; // ASCIZ string... if flags[2]
	struct { // info on loaded modules... if flags[3]
		int mod_count;
		struct mb_mod *mod_addr;
	} module_info;
	union { //don't depend on this being correct! // symbol table... if flags[4] or flags[5]
		struct {
			int tabsize;
			int strsize;
			void* tbl;
			int reserved;
		} aout_header;
		struct {
			int num;
			int size;
			void* addr;
			int shndx;
		} elf_header;
	} header;
	struct { // mmap table... if flags[6]
		int length;
		void* addr;
	} mmap_info;
	struct { // drive info... if flags[7]
		int length;
		void* addr;
	} drive_info;
	void* config_table; // BIOS config table... if flags[8]
	char* boot_loader_name; // the name of the bootloader... if flags[9]
	struct { // apm info... if flags[10]
		short int version;
		short int cseg;
		int offset;
		short int cseg16;
		short int dseg;
		short int flags;
		short int cseg_len;
		short int cseg_16_len;
		short int dseg_len;
	}* apm_table;
	struct { // vbe info... if flags[11]
		int vbe_control_info;
		int vbe_mode_info;
		short int vbe_mode;
		short int vbe_interface_seg;
		short int vbe_interface_len; //THIS MAY BE 32 bits!
	} vbe_info;
};

void k_main(struct mboot_info* mbd, unsigned int magic ) {
	init_serial();
	vmem = (unsigned char*)0xB8000;
	//Multiboot crap.
	init_con();
	k_cls();
	if (magic != 0x2BADB002) { // not multiboot!
		k_swrite("\e[1;44;37mI'm a multiboot kernel, dammit! Use a multiboot bootloader!", OUT_STD);
		panic();
	}
	//k_printf("1");
	if (mbd->flags & 0x4) { // module info
		k_swrite("modinfo\n", OUT_STD);
		k_iwrite (mbd->module_info.mod_count, OUT_STD);
		k_swrite("\n",OUT_STD);
		for (int i = 0; i < mbd->module_info.mod_count; i++) {
			char* buf = mbd->module_info.mod_addr[i].module_id;
			buf++;
			while (*(buf) && *(buf-1) != ' ') buf++;
			k_swrite("Loading module ", OUT_STD);
			k_swrite(buf, OUT_STD);
			if (strncmp("font ", buf, 5) == 0) {
				set_font(mbd->module_info.mod_addr[i].start, buf[5] - '0');
				k_swrite("... \e[1;34mDONE\e[0m\n", OUT_STD);
			} else {
				k_swrite("... \e[1;31mUnknown module name!\e[0m\n", OUT_STD);
			}
		}
		pft();		
		//for (int i = 0; i < 100; i++)
		//	spin(1000000);
		
	}
	//
	char *hex = "0123456789ABCDEF";
	//char u;
	//while (u=read_serial)
	//	write_serial(u);
	k_cls();
//	for (int i = 0; i < 80*25*2; i+= 2) {
//		vmem[i+1] = (unsigned char)0x20;
//		vmem[i] = 'A';
//		//spin(100);
//	}
	
	//scroll (5);
	//spin(10000000);
	k_cls();
	
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
	k_swrite("test\ntest2",OUT_DBG);
}

