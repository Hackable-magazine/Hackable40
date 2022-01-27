#include <stdint.h>
#include "uart.h"
#include "util.h"
#include "mbox.h"
#include "fb.h"

//extern volatile unsigned int mbox[36];
volatile unsigned int  __attribute__((aligned(16))) mbox[36];

int kernelmain(void)
{
	init_uart();
	puts("\r\n\r\n\r\nBonjour Hackable !\r\n");

	struct fbst fb;
	init_fb(mbox, &fb);
	if(fb.fbp) {
		puts("Framebuffer address: 0x");
		printhex((unsigned int)fb.fbp);
		puts("\r\n");
	} else {
		puts("Unable to get framebuffer!\r\n");
	}

    // get the board's unique serial number with a mailbox cal
	// https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
    mbox[0] = 8*4;                  // length of the message 8*4bytes
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // Response: Length: in bytes (expecting 2 bytes in [5][6])
    mbox[4] = 0;					// Request: Length: in bytes (bytes in [5][6] not matters)
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if (mbox_call(MBOX_CH_PROP, mbox)) {
        puts("Serial number = ");
        printhex(mbox[6]);
        printhex(mbox[5]);
        puts("\r\n");
    } else {
        puts("Error getting serial number!\r\n");
    }

    mbox[0]=8*4;
    mbox[1]=MBOX_REQUEST;
    mbox[2]=MBOX_TAG_GETARMMEM;
    mbox[3]=8;
    mbox[4]=0;
    mbox[5]=0;
    mbox[6]=0;
    mbox[7]=MBOX_TAG_LAST;
    if (mbox_call(MBOX_CH_PROP, mbox)) {
        puts("ARM memory start at 0x");
        printhex(mbox[5]);
        puts(" - ");
		int mem=mbox[6]/1024/1024;
		printdec(mem);
		puts(" Mo\r\n");
    } else {
        puts("Error getting ARM memory!\r\n");
    }

    mbox[0]=8*4;
    mbox[1]=MBOX_REQUEST;
    mbox[2]=MBOX_TAG_GETVCOREMEM;
    mbox[3]=8;
    mbox[4]=0;
    mbox[5]=0;
    mbox[6]=0;
    mbox[7]=MBOX_TAG_LAST;
    if (mbox_call(MBOX_CH_PROP, mbox)) {
        puts("Videocore memory start at 0x");
        printhex(mbox[5]);
        puts(" - ");
		int mem=mbox[6]/1024/1024;
		printdec(mem);
		puts(" Mo\r\n");
    } else {
        puts("Error getting Videocore memory!\r\n");
    }

    mbox[0]=8*4; 					// length of the message en octets
    mbox[1]=MBOX_REQUEST;			// this is a request message
    mbox[2]=MBOX_TAG_GETCORETEMP;	// the tag id
    mbox[3]=8;						// buffer size (Response: Length: 8 in https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface) en octets
    mbox[4]=4;						// len (Request: Length: 4) en octets
    mbox[5]=0x000000001;			// ID
    mbox[6]=0;
    mbox[7]=MBOX_TAG_LAST;
    if (mbox_call(MBOX_CH_PROP, mbox)) {
        puts("SoC temperature: ");
		int temp=mbox[6];
		printdec(temp);
		puts("\r\n");
    } else {
        puts("Error getting SoC temperature!\r\n");
    }

	if(!fb.fbp)
		return 0;

    puts("width: ");
    printdec(fb.width);
    puts("\r\n");
    puts("height: ");
    printdec(fb.height);
    puts("\r\n");
    puts("address: ");
    printhex((unsigned int)fb.fbp);
    puts("\r\n");

    unsigned char *ptr=fb.fbp;

    for(int y=0; y<fb.height; y++) {
        for(int x=0; x<fb.width; x++) {
            if(y%60==0)
                *((unsigned int*)ptr)=0x00FF0000;
            else if (y%40==0)
                *((unsigned int*)ptr)=0x0000FF00;
            else if (y%20==0)
                *((unsigned int*)ptr)=0x000000FF;
            else
                *((unsigned int*)ptr)=0x00000000;
            ptr+=4;
        }
    }


	while(1) {
		;
	}

	return 0;
}
