
ARM-GNU ?= arm-linux-androideabi

COPTS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -std=gnu99 -mthumb -mthumb-interwork

OBJ_FILES = start.o boot.o memset.o video.o

kernel: kernel.img

all:  kernel

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s


start.o: start.s
	$(ARM-GNU)-gcc $(COPTS) -c start.s -o start.o

boot.o: boot.c start.h
	$(ARM-GNU)-gcc $(COPTS) -c boot.c -o boot.o

memset.o: memset.s
	$(ARM-GNU)-gcc $(COPTS) -c memset.s -o memset.o

video.o: video.c video.h	
	$(ARM-GNU)-gcc $(COPTS) -c video.c -o video.o

kernel.img: loader $(OBJ_FILES)
	$(ARM-GNU)-ld $(OBJ_FILES) -T loader -o boot.elf
	$(ARM-GNU)-objdump -D boot.elf > boot.list
#	$(ARM-GNU)-objcopy boot.elf -O ihex boot.hex
	$(ARM-GNU)-objcopy boot.elf -O binary kernel.img

run: kernel.img
	emulator -verbose -avd phone -shell -show-kernel -qemu -kernel kernel.img
