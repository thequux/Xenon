#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv) {
	(void)argc;
	(void)argv;
	char buf;
	char ckxor = 0;
	while (read (0, &buf, 1)>0) {
		ckxor ^= buf;
	}
	printf ("%hhx\n", ckxor);
}
