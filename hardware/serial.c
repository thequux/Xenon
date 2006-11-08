#include <ctools.h>
// this file stolen from OSFAQ, until further notice...
#define PORT 0x3f8   /* ttyS0 */

void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int serial_recieved() {
   return inb(PORT + 5) & 1;
}

char read_serial() {

   while (serial_recieved() == 0) {
      continue;
   }

   return inb(PORT);
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}

void write_serial(char a) {

   while (is_transmit_empty() == 0) {
      continue;
   }

   outb(PORT,a);

}

// further notice.
//
// No really, from here on, it's mine.

void ser_out (unsigned char b) {
	while ((inb (0x3fd) & 0x20) == 0)
		;
	outb(0x3f8, b);
}
