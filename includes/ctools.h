/* output types */
#define OUT_DBG 1
#define OUT_STD 0

#include "config.h"
#define NULL ((void*)(0))
int strlen(void* str);

void spin(unsigned long int cycles);
void dbg(char c);  /* in asm */
int parse_scbuf (unsigned char* buf);
int memcpy (void* dest, const void* src, int count);
int memset (void* buf, int val, int count);
int strcmp (char* s1, char* s2);
int strncmp(char* s1, char* s2, int n);

void strrev(char* s);

// serial I/O...
void init_serial();
char read_serial();
void write_serial(char a);

// IO ports...
//void outb (short unsigned int port, unsigned char byte);
//unsigned char inb  (short unsigned int port);

static __inline__ void outb(unsigned short port, unsigned char val)
{
   __asm__ volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

static __inline__ unsigned char inb(unsigned short port)
{
   unsigned char ret;
   __asm__ volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}


