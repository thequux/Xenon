#include "ctools.h"
int strlen(void* str0) {
	int i = 0;
	char* str = (char*)str0;
	while (*str++) i++;
	return i;
}

int memcpy(void* dest, const void* src, int count) {
	while (count--)
		*((char*)dest++) = *((char*)src++);
	return 0;
}

int memset(void* buf, int val, int count) {
	while (count--)
		*((char*)buf++) = (char)val;
	return 0;
}

int strcmp(char* s1, char* s2) {
	while (*s1 == *s2 && *s1 && *s2) {
		s1++;
		s2++;
	}
	if (*s1 < *s2) return -1;
	if (*s1 == *s2) return 0;
	return 1;
}
int strncmp(char* s1, char* s2, int n) {
	
	while (*s1 && *s2 && *s1==*s2 && n > 0) {
		s1++;
		s2++;
		n--;
	}
	if (n == 0) return 0;
	if (*s1 < *s2) return -1;
	if (*s1 == *s2) return 0;
	 return 1;
}

void strrev(char* str) {
	char tmp;
	char* back = str;

	while (*back) back++; //seek to end of string
	back--;

	while (back > str) {
		tmp = *str;
		*str++ = *back;
		*back-- = tmp;
	}
	
}
/*
int printf() {
	;
}
*
static __inline__ void outb(unsigned short port, unsigned char val)
{
   asm volatile("outb %0,%1"::"a"(val), "Nd" (port));
}

static __inline__ unsigned char inb(unsigned short port)
{
   unsigned char ret;
   asm volatile ("inb %1,%0":"=a"(ret):"Nd"(port));
   return ret;
}

*/
