#include "ctools.h"
#include "video.h"
#include <kalloc.h>
#include <pci.h>
//#define VMMMMEM_C(x,y)  (vmem+(((y)*80+(x))*2))
volatile unsigned char* vmem;
void panic();
void init_vga();
void disp_char(char val);
int pft();
void powerdown() __attribute__((noreturn));
struct __attribute__ ((packed)) mb_mod {
	void *start;
	void *end;
	char *module_id; // this is up to me...
	int reserved;

};
extern struct {
	unsigned int low;
	unsigned int high;
} cpu_freq;

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
	/*struct { // apm info... if flags[10]
		short int version;
		short int cseg;
		int offset;
		short int cseg16;
		short int dseg;
		short int flags;
		short int cseg_len;
		short int cseg_16_len;
		short int dseg_len;
	}* apm_table; */
	struct apm_info_t *apm_table; // if flags[10]
	struct { // vbe info... if flags[11]
		int vbe_control_info;
		int vbe_mode_info;
		short int vbe_mode;
		short int vbe_interface_seg;
		short int vbe_interface_len; //THIS MAY BE 32 bits!
	} vbe_info;
};
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
void k_main(struct mboot_info* mbd, unsigned int magic ) {
	init_serial();
	vmem = (unsigned char*)0xB8000;
	//Multiboot crap.
	init_con();
	CON.cls(&CON);
	printf("test");
	//k_cls();
	if (magic != 0x2BADB002) { // not multiboot!
		k_swrite("\e[1;44;37mI'm a multiboot kernel, dammit! Use a multiboot bootloader!", OUT_STD);
		panic();
	}
	//k_printf("1");
	//kalloc_init();
	if (mbd->flags & 0x8) { // module info
		k_swrite("modinfo\n", OUT_STD);
		k_iwrite (mbd->module_info.mod_count, OUT_STD);
		k_swrite("\n",OUT_STD);
		for (int i = 0; i < mbd->module_info.mod_count; i++) {
			char* buf = mbd->module_info.mod_addr[i].module_id;
			buf++;
			while (*(buf) && *(buf-1) != ' ') buf++;
			printf ("Loading module [%s]...", buf);
			//k_swrite("Loading module ", OUT_STD);
			//k_swrite(buf, OUT_STD);
			if (strncmp("font ", buf, 5) == 0) {
				struct font_t* fnt = mbd->module_info.mod_addr[i].start;
				font = fnt;
				//set_font(mbd->module_info.mod_addr[i].start, buf[5] - '0');
				k_swrite(" \e[1;34mDONE\e[0m\n", OUT_STD);
				printf ("<w:%d h:%d bw:%d gs:%d ng:%d>\n", fnt->w, fnt->h, fnt->w_byte, fnt->glyph_size, fnt->nGlyphs);
				mark_used (mbd->module_info.mod_addr[i].start,mbd->module_info.mod_addr[i].end - mbd->module_info.mod_addr[i].start);
			} else {
				k_swrite(" \e[1;31mUnknown module name!\e[0m\n", OUT_STD);
			}
		}
	}
	if (mbd->flags & 0x400) {
		// apm avaliable...
		apm_info.valid = ~ 0x0;
		apm_info.version = mbd->apm_table->version;
		apm_info.cseg = mbd->apm_table->cseg;
		apm_info.offset = mbd->apm_table->offset;
		apm_info.dseg = mbd->apm_table->dseg;
		apm_info.flags = mbd->apm_table->flags;
		apm_info.cseg_len = mbd->apm_table->cseg_len;
		apm_info.cseg_16 = mbd->apm_table->cseg_16;
		apm_info.cseg_16_len = mbd->apm_table->cseg_16_len;
		apm_info.dseg_len = mbd->apm_table->dseg_len;
		printf("CSEG: %x\nCSEG_LEN: %x\nOFFSET: %x\n", apm_info.cseg, apm_info.cseg_len, apm_info.offset);
	} else {
		apm_info.valid = 0x00;
	}
	//unsigned int instr;
	//instr = cpu_freq.low / 10;
	//double cpf = instr / 1000.0;
//	init_vga();
	//k_s_char('a');
	printf ("Clock speed: %d\n", cpu_freq.low); //(int)cpf, (int)(1000*(cpf-(int)cpf)));
	//
	char *hex = "0123456789ABCDEF";
	pciScanBus();
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
}

