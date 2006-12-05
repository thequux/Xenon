#define BLOCK_SIZE	0x1000
void kalloc_init();
void* kalloc (int count);
void mark_used (void* offset, int len);
