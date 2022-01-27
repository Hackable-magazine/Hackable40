#include <stdint.h>
#include "uart.h"

void init_uart(void)
{
	// Active mini-uart
	AUX_ENB |= 1;
	// 8 bit de data
	MU_LCR = 3;
	// 115200 bps
	MU_BAUD = 270;
	// GPIO 14 & 15 en alt5
	GPFSEL1 &= ~((7 << 12) | (7 << 15));
	GPFSEL1 |=   (2 << 12) | (2 << 15);

	// Pas de pull-up/down.
	GPPUD = 0;
	// pause
	for(uint8_t i = 0; i < 200; i++)
		asm volatile ("nop");
	GPPUDCLK0 = (2 << 14) | (2 << 15);
	// pause
	for(uint8_t i = 0; i < 200; i++)
		asm volatile ("nop");
	GPPUDCLK0 = 0;
	GPPUD = 0;

	MU_CNTL = 3; // active Tx & Rx
}


void putc(char c)
{
	while(!(MU_LSR & 0x20))
		;
	MU_IO = c;
}

void puts(const char *s)
{
	while(*s)
		putc(*s++);
}
