#pragma once

#include "mmio.h"

// Auxiliary enables
#define AUX_ENB (*(volatile unsigned *)(MU_BASE + 0x04))
// Mini Uart I/O Data
#define MU_IO   (*(volatile unsigned *)(MU_BASE + 0x40))
// Mini Uart Line Control
#define MU_LCR  (*(volatile unsigned *)(MU_BASE + 0x4c))
// Mini Uart Line Status
#define MU_LSR  (*(volatile unsigned *)(MU_BASE + 0x54))
// Mini Uart Extra Control
#define MU_CNTL (*(volatile unsigned *)(MU_BASE + 0x60))
// Mini Uart Baudrate
#define MU_BAUD (*(volatile unsigned *)(MU_BASE + 0x68))

// GPIO Function Select 1
#define GPFSEL1 (*(volatile unsigned *)(GP_BASE + 0x04))
// GPIO Pin Pull-up/down Enable
#define GPPUD   (*(volatile unsigned *)(GP_BASE + 0x94))
// GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK0   (*(volatile unsigned *)(GP_BASE + 0x98))

void init_uart(void);
void putc(char c);
void puts(const char *s);
