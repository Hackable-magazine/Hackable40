#include <stdint.h>
#include "uart.h"

void printhex(unsigned int d)
{
	char n;
	for(int c=28;c>=0;c-=4) {
		// get highest tetrad
		n=(d>>c)&0xF;
		// 0-9 => '0'-'9', 10-15 => 'A'-'F'
		n+=n>9?0x37:0x30;
		putc(n);
	}
}

int strlen(char s[])
{
	int i=0;
	while(s[i]!= '\0') {
		++i;
	}
	return i;
}

void reverse(char s[])
{
	int c, i, j;
	for(i=0, j=strlen(s)-1; i<j; i++, j--) {
		c=s[i];
		s[i]=s[j];
		s[j]=c;
	}
}

void itoa(unsigned int n, char s[])
{
	int i=0;
	do {
		s[i++]=n%10+'0';
	} while((n/=10)>0);
	s[i]='\0';
	reverse(s);
}

void printdec(unsigned int d)
{
	char s[16];
	itoa(d, s);
	for(int i=0; i<strlen(s); i++) {
		putc(s[i]);
	}
}
