#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
struct ptable 
{
	unsigned char bootid;
	unsigned char beghead;  /* beginning head number */
	unsigned char begsect;  /* beginning sector number */
	unsigned char begcyl;   /* 10 bit nmbr, with high 2 bits put in begsect */	
	unsigned char systid;   /* Operating System type indicator code */
	unsigned char endhead;  /* ending head number */
	unsigned char endsect;  /* ending sector number */
	unsigned char endcyl;   /* also a 10 bit nmbr, with same high 2 bit trick */
	unsigned int relsect;            /* first sector relative to start of disk */
	unsigned int numsect;            /* number of sectors in partition */
} __attribute__((packed)) ;
struct sector {
	char pad[446];
	ptable part[4];
	uint16_t sig;
} __attribute__((packed)) ;

int main(int argc, char** argv) {
	sector* dsk;
	int dskFD = open(argv[1], O_RDONLY);
	if (dskFD == -1) perror ("open");
	dsk = (sector*) mmap(NULL, 512, PROT_READ, MAP_SHARED, dskFD, 0);
	if (dsk == (sector*)(void*)(-1)) perror("mmap");
	assert(sizeof(sector) == 512);
	for(int x = 0; x<4; x++) {
		printf("%d: %c %u %u\t\tmount -o loop,offset=%u,sizelimit=%u %s   /\n",
			x,
			((dsk->part[x].bootid == 0)?' ':'b'),
			dsk->part[x].relsect /2048,
			dsk->part[x].numsect /2048,
			dsk->part[x].relsect,
			dsk->part[x].numsect,
//			dsk->part[x].relsect * 512,
//			dsk->part[x].numsect * 512,
			argv[1]);
	}
}
