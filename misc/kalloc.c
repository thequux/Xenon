#include <ctools.h>
#include <kalloc.h>
#include <video.h>
//#define MEMPOOL_LEN	0x1000000
#define BLOCK_SIZE	0x1000
//#define ATOM_COUNT	(MEMPOOL_LEN / ATOM_SIZE)

extern unsigned int kalloc_len;
static int block_count;
static int alloc_tbl_overhead;
struct kalloc_block {
	char data[BLOCK_SIZE];
};
extern struct kalloc_block* kalloc_pool;
// one allocation "atom" is exactly 4K ... this will be important when I do
// paging.

struct kalloc_desc {
	void*		addr;
	unsigned short	index; // there probably isn't a point to having this...
	BOOL		free;
}; // 8-byte struct with 1 byte free...

extern struct kalloc_desc kalloc_tbl[];

void kalloc_init() {
//	alloc_tbl = (struct kalloc_desc*) kalloc_pool;
	block_count = kalloc_len / BLOCK_SIZE; 
	alloc_tbl_overhead = (block_count * sizeof(struct kalloc_desc)) / BLOCK_SIZE;
	for (int i = 0; i < block_count; i++) {
		kalloc_tbl[i].addr = (void*)(kalloc_pool + i);
		kalloc_tbl[i].index = i;
		kalloc_tbl[i].free = TRUE;
	}
	for (int i = 0; i < alloc_tbl_overhead; i++) {
		kalloc_tbl[i].free = FALSE;
	}
	
	int len_sz, blk_sz;
	char len_sfx, blk_sfx;
	
	if (kalloc_len < 0x400) {
		len_sz  = kalloc_len;
		len_sfx = 'b';
	} else if (kalloc_len < 0x1000000) {
		len_sz  = kalloc_len >> 10;
		len_sfx = 'K';
	} else {
		len_sz  = kalloc_len >> 20;
		len_sfx = 'M';
	}
	
	if (BLOCK_SIZE < 0x400) {
		blk_sz  = BLOCK_SIZE;
		blk_sfx = 'b';
	} else if (BLOCK_SIZE < 0x1000000) {
		blk_sz  = BLOCK_SIZE >> 10;
		blk_sfx = 'K';
	} else if (BLOCK_SIZE < 0x400000000) {
		blk_sz  = BLOCK_SIZE >> 20;
		blk_sfx = 'M';
	} else {
		blk_sz  = BLOCK_SIZE >> 30;
		blk_sfx = 'G';
	}
	printf ("Kernel allocator initialized\n"
		"      Alloc pool:             %d%c reserved\n"
		"      Block size:             %d%c\n"
		"      Blocks used (tables):   %d\n",
		len_sz, len_sfx,
		blk_sz, blk_sfx,
		alloc_tbl_overhead);
}

void* kalloc (int count) {
	int contig = 0;
	int base = 0;
	for (int i = alloc_tbl_overhead; i < block_count; i++) {
		if (! kalloc_tbl[i].free) {
			if (!contig)
				base = i;
			contig ++;
		} else {
			contig = 0;
		}
		if (contig >= count) break;
	}
	for (int i = base; i < count; i++) 
		kalloc_tbl[i].free = FALSE;
	return kalloc_tbl[base].addr;
}

void mark_used (void* addr, int len) {
	int offs = (char*)addr - (char*)kalloc_pool;
	len += (offs%4096);
	offs -= offs%4096;
	offs /= 4096;
	len = len + 4096 - len%4096;
	len /= 4096;
	while (len) {
		kalloc_tbl[offs].free = FALSE;
		offs++;
		len--;
	}
}
