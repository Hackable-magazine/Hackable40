#pragma once

// mapping périphériques
#define IO_BASE 0x3f000000
// mapping mini Uart
#define MU_BASE (IO_BASE + 0x215000)
// mapping GPIO
#define GP_BASE (IO_BASE + 0x200000)
// videocore mbox system
#define VCORE_MBOX  (IO_BASE+0x0000B880)

