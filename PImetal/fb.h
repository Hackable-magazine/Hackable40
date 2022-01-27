#pragma once

struct fbst {
    unsigned char *fbp;
    unsigned int width;
    unsigned int height;
    unsigned int pitch;
    unsigned int isrgb;
};

unsigned char *init_fb(volatile unsigned int *mbox, struct fbst *fb);
