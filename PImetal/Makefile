CROSS=aarch64-none-elf-
CC=$(CROSS)gcc
CFLAGS=-Wall -O0 -g -ffreestanding
LDSCRIPT=rpi3.ld

OBJS=crt0.o uart.o util.o mbox.o fb.o hello.o

all: hello.bin

hello.elf: $(OBJS) $(LDSCRIPT)
	$(CROSS)ld -o $@ $(OBJS) -T$(LDSCRIPT) -Map hello.map

hello.bin: hello.elf
	$(CROSS)objcopy -O binary $< $@

clean:
	rm -f $(OBJS) *.bin *.elf *.map *.lst

mrproper:
	rm -f $(OBJS) *.bin *.elf *.map *.lst *~

