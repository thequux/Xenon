#include <elf.h>
#include <ctools.h>
#include <video.h>
#include <driver.h>
void print_symtab(int num, int size,
		  void* addr, int shndx) {
	(void)size;
	(void)num;
	(void)addr;
	(void)shndx;
	return;
	char* str_tab = (char*)(((Elf32_Shdr*)addr + shndx)->sh_addr);
	Elf32_Sym * symtab = 0;
	for (int i = 0; i <= num; i++) {
		printf ("%24s]\t%08x\n",
			str_tab+((Elf32_Shdr*)addr+i)->sh_name,
			((Elf32_Shdr*)addr+i)->sh_addr);
		if ((((Elf32_Shdr*)addr+i)->sh_type) == SHT_SYMTAB){
			symtab = (Elf32_Sym *)(((Elf32_Shdr*)addr+i)->sh_addr);
			printf ("^");
		}
		//if (strcmp(str_tab+(((Elf32_Shdr*)addr+i)->sh_name), ".symtab")== 0)
		//	symtab = (Elf32_Sym *)(((Elf32_Shdr*)addr+i)->sh_addr);
	}
	printf ("symtab: %08x\n", symtab);
	for (int i = 0; i < 40; i++) {
		printf ("[%s]\t%08x\n",
			str_tab+(symtab[i].st_name)-4,
			(symtab[i].st_value));
	}
}
