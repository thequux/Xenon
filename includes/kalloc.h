#define BLOCK_SIZE	0x1000
struct page_t {
	unsigned int p:1;
	unsigned int w:1;
	unsigned int u:1;
	unsigned int pwt:1;
	unsigned int pcd:1;
	unsigned int a:1;
	unsigned int resv:1;
	unsigned int pat:1;
	unsigned int g:1;
	unsigned int avail:3;	// for my use only
	unsigned int base:20;
};
struct page_dir {
	
	unsigned int p:1;
	unsigned int w:1;
	unsigned int u:1;
	unsigned int pwt:1;
	unsigned int pcd:1;
	unsigned int a:1;
	unsigned int dirty:1;
	unsigned int ps:1;
	unsigned int g:1;
	unsigned int avail:3;	// for my use only
	unsigned int base:20;

};
struct pginfo_t {
	struct page_t table[1023][1024];
	struct page_dir dir[1024];
};

extern struct pginfo_t pginfo;

void kalloc_init();
void* kalloc (int count);
void mark_used (void* offset, int len);
