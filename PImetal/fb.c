#include <stdint.h>
#include "uart.h"
#include "util.h"
#include "mbox.h"
#include "fb.h"

extern volatile unsigned int mbox[36];

unsigned char *init_fb(volatile unsigned int *mbox, struct fbst *fb)
{
	// sending many tags at once
    mbox[0] = 35*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = 0x48003;  //set phy wh
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = 1920;         //FrameBufferInfo.width
    mbox[6] = 1080;          //FrameBufferInfo.height
    mbox[7] = 0x48004;  //set virt wh
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1920;        //FrameBufferInfo.virtual_width
    mbox[11] = 1080;         //FrameBufferInfo.virtual_height
    mbox[12] = 0x48009; //set virt offset
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0;           //FrameBufferInfo.x_offset
    mbox[16] = 0;           //FrameBufferInfo.y.offset
    mbox[17] = 0x48005; //set depth
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32;          //FrameBufferInfo.depth
    mbox[21] = 0x48006; //set pixel order
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1;           //RGB, not BGR preferably
    mbox[25] = 0x40001; //get framebuffer, gets alignment on request
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096;        //FrameBufferInfo.pointer
    mbox[29] = 0;           //FrameBufferInfo.size
    mbox[30] = 0x40008; //get pitch
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0;           //FrameBufferInfo.pitch
    mbox[34] = MBOX_TAG_LAST;

	if (mbox_call(MBOX_CH_PROP, mbox) && mbox[20]==32 && mbox[28]!=0) {
        mbox[28]&=0x3FFFFFFF;   //convert GPU address to ARM address
        fb->width=mbox[5];          //get actual physical width
        fb->height=mbox[6];         //get actual physical height
        fb->pitch=mbox[33];         //get number of bytes per line
        fb->isrgb=mbox[24];         //get the actual channel order
        fb->fbp=(void*)((unsigned long)mbox[28]);
    } else {
        puts("Unable to set framebuffer!\r\n");
		return 0;
    }

	return fb->fbp;
}
