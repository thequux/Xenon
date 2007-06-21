#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv) {
	(void)argc;
	(void)argv;
	unsigned char buf;
	unsigned char cksum = 0;
	while (read (0, &buf, 1)>0) {
		cksum +=buf;
	}
	printf ("%hhx\n", cksum);
}
