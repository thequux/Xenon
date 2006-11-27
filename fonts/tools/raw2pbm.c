// 8x16
//
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char** argv) {
	int in = open (argv[1], O_RDONLY);
	int out = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);

	int line = 0; // scanline
	int row = 0; // row of glyphs
	int glyph; // glyph in row
	unsigned char buf[9];
	write (out, "P4\n",3);
	write (out, "144 272\n", 8);
	for (row = 0; row < 16; row++) {
		for (line = 0; line < 16; line++) {
			unsigned char* buf2 = buf;
			for(glyph = 0; glyph < 16; glyph++) {
				lseek (in, ((row * 16 + glyph) * 32 + line), SEEK_SET);
				read (in, buf2, 1);
				buf2++;
				if (glyph == 7 || glyph == 15) {
					buf[8] =                 (buf[7] << 1);
					buf[7] = (buf[7] >> 7) | (buf[6] << 2);
					buf[6] = (buf[6] >> 6) | (buf[5] << 3);
					buf[5] = (buf[5] >> 5) | (buf[4] << 4);
					buf[4] = (buf[4] >> 4) | (buf[3] << 5);
					buf[3] = (buf[3] >> 3) | (buf[2] << 6);
					buf[2] = (buf[2] >> 2) | (buf[1] << 7);
					buf[1] = (buf[1] >> 1) ;
					write (out, buf, 9);
					buf2 = buf;
				}

			}
		}
		for (int i = 0; i < 9; i++)
			buf[i] = 0;
		write (out, buf, 9);
		write (out, buf, 9);
	}
	(void) argc;
	return 0;
}
