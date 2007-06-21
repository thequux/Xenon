#ifndef XE_CTOOLS_H
#define XE_CTOOLS_H
/* output types */
#define OUT_DBG 1
#define OUT_STD 0

#include "config.h"
// Standard C defines; also, data types
#ifndef NULL
#define NULL ((void*)(0))
#endif
int strlen(void* str);

void spin(unsigned long int cycles);
void dbg(char c);  /* in asm */
void panic();
int parse_scbuf (unsigned char* buf);
int memcpy (void* dest, const void* src, int count);
int memset (void* buf, int val, int count);
int strcmp (char* s1, char* s2);
int strncmp(char* s1, char* s2, int n);

void strrev(char* s);
/*
;             +----------------------+
;     0       | version              |
;     2       | cseg                 |
;     4       | offset               |
;     8       | cseg_16              |
;     10      | dseg                 |
;     12      | flags                |
;     14      | cseg_len             |
;     16      | cseg_16_len          |
;     18      | dseg_len             |
;             +----------------------+
*/
struct __attribute__((packed)) apm_info_t {
	short version;
	short cseg;
	unsigned int offset;
	unsigned short cseg_16;
	unsigned short dseg;
	unsigned short flags;
	unsigned short cseg_len;
	unsigned short cseg_16_len;
	unsigned short dseg_len;
	unsigned int valid;
};

extern struct apm_info_t apm_info;
// serial I/O...
void init_serial();
char read_serial(int port);
void write_serial(int port, char a);

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

static __inline__ void outw(unsigned short port, unsigned short val)
{
   __asm__ volatile("outw %0,%1"::"a"(val), "Nd" (port));
}

static __inline__ unsigned short inw(unsigned short port)
{
   unsigned short ret;
   __asm__ volatile ("inw %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

static __inline__ void outl(unsigned short port, unsigned int val)
{
   __asm__ volatile("outl %0,%1"::"a"(val), "Nd" (port));
}

static __inline__ unsigned int inl(unsigned short port)
{
   unsigned int ret;
   __asm__ volatile ("inl %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

#endif
