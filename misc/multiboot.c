#include <ctools.h>
#include <video.h>
#include <kalloc.h>
#include <elf.h>
struct __attribute__ ((packed)) mb_mod {
	void *start;
	void *end;
	char *module_id; // this is up to me...
	int reserved;

};
#define MBI_MEMINFO	(1<<0)
#define MBI_BOOT_DEV	(1<<1)
#define MBI_CMDLINE	(1<<2)
#define MBI_MODINFO	(1<<3)
#define MBI_SYM_AOUT	(1<<4)
#define MBI_SYM_ELF	(1<<5)
#define MBI_MMAP	(1<<6)
#define MBI_DRIVE_INFO	(1<<7)
#define MBI_BIOS_CONFIG	(1<<8)
#define MBI_BL_NAME	(1<<9)
#define MBI_APMINFO	(1<<10)
#define MBI_VBEINFO	(1<<11)
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
void do_multiboot(struct mboot_info *mbd) {
	if (mbd->flags & MBI_MODINFO) { // module info
		panic();
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
	if (mbd->flags & MBI_APMINFO) {
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

/*	if (mbd->flags & MBI_SYM_ELF) {
		print_symtab(
			mbd->header.elf_header.num,
			mbd->header.elf_header.size,
			mbd->header.elf_header.addr,
			mbd->header.elf_header.shndx);
			
		printf ("Symtab @ xp /%dxb 0x%x ;\n", 
			mbd->header.elf_header.shndx,
			mbd->header.elf_header.addr + mbd->header.elf_header.size * mbd->header.elf_header.shndx);
	}
*/
}
