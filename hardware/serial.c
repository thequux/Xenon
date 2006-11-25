#include <ctools.h>
// this file stolen from OSFAQ, until further notice...
#define PORT 0x3f8   /* ttyS0 */

static char msg[] = "\e[2J\e[1;1H/dev/ttyS0 ready\r\n";
static int ser_ports[] = {0x3f8, 0x2f8, 0x3e8, 0x2e8 };
void init_serial_real(int port) {
	char* lmsg;
	int ioport = ser_ports[port];
	msg[19] = ((char)port) + '0';
	outb(ioport + 1, 0x00);    // Disable all interrupts
	outb(ioport + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(ioport + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(ioport + 1, 0x00);    //                  (hi byte)
	outb(ioport + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(ioport + 2, 0xc7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(ioport + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	outb(ioport + 1, 0x01);
	lmsg = msg - 1;
	//while (*(++lmsg))
	//	write_serial(port, *lmsg);
}
void init_serial() {
   init_serial_real (0);
   init_serial_real (1);
}

int serial_recieved(int port) {
   return inb(ser_ports[port] + 5) & 1;
}

char read_serial(int port) {

   while (serial_recieved(port) == 0) {
      continue;
   }

   return inb(ser_ports[port]);
}

int is_transmit_empty(int port) {
   return inb(ser_ports[port] + 5) & 0x20;
}

void write_serial(int port, char a) {

   while (is_transmit_empty(port) == 0) {
      continue;
   }

   outb(ser_ports[port],a);

}

// further notice.
//
// No really, from here on, it's mine.

void ser_ou_t (unsigned char b) {
	while ((inb (0x3fd) & 0x20) == 0)
		;
	outb(0x3f8, b);
}
