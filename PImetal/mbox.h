#pragma once

#include "mmio.h"

/* mailbox message buffer */
//extern volatile unsigned int mbox[36];

#define MBOX_READ       ((volatile unsigned int*)(VCORE_MBOX+0x0))
#define MBOX_POLL       ((volatile unsigned int*)(VCORE_MBOX+0x10))
#define MBOX_SENDER     ((volatile unsigned int*)(VCORE_MBOX+0x14))
#define MBOX_STATUS     ((volatile unsigned int*)(VCORE_MBOX+0x18))
#define MBOX_CONFIG     ((volatile unsigned int*)(VCORE_MBOX+0x1C))
#define MBOX_WRITE      ((volatile unsigned int*)(VCORE_MBOX+0x20))
#define MBOX_RESPONSE   0x80000000
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

#define MBOX_REQUEST    0

/* channels */
#define MBOX_CH_POWER   0
#define MBOX_CH_FB      1
#define MBOX_CH_VUART   2
#define MBOX_CH_VCHIQ   3
#define MBOX_CH_LEDS    4
#define MBOX_CH_BTNS    5
#define MBOX_CH_TOUCH   6
#define MBOX_CH_COUNT   7
#define MBOX_CH_PROP    8

/* tags */
#define MBOX_TAG_GETSERIAL		0x00010004
#define MBOX_TAG_GETARMMEM		0x00010005
#define MBOX_TAG_GETVCOREMEM	0x00010006
#define MBOX_TAG_GETCORETEMP	0x00030006
#define MBOX_TAG_LAST			0

int mbox_call(unsigned char ch, volatile unsigned int *mbox);
