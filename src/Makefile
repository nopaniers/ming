#------------------------------------------------------------------------------
# Makefile for Ming OS
#------------------------------------------------------------------------------
#
# Make the OS and run on the emulator
#
# > make run
#
# Compile the OS and run the emulator, pausing at beginning to attach gdb:
#
# > make debug
#
# After which (in a different terminal) you can debug using
#
# > make debugger
#
#------------------------------------------------------------------------------

ARM-GNU ?= arm-linux-androideabi

COPTS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -mthumb-interwork -std=gnu99 -mthumb -mthumb-interwork

OBJ_FILES = start.o boot.o memset.o video.o timer.o hello.o

RUSTC = rustc
CLANG = clang

kernel: kernel.img

all:  kernel

clean:
	rm -f *.o *.bin *.hex *.elf *.list *.img *.bc *.clang.s

start.o: start.s ../resources/ming_logo2.raw
	$(ARM-GNU)-gcc $(COPTS) -c start.s -o start.o

boot.o: boot.c start.h
	$(ARM-GNU)-gcc $(COPTS) -c boot.c -o boot.o

memset.o: memset.s
	$(ARM-GNU)-gcc $(COPTS) -c memset.s -o memset.o

# video.o: video.c video.h	
#	$(ARM-GNU)-gcc $(COPTS) -c video.c -o video.o

timer.o: timer.c timer.h
	$(ARM-GNU)-gcc $(COPTS) -c timer.c -o timer.o


../resources/ming_logo2.raw: ../resources/ming_logo2.png
	../resources/convert_to_565 ../resources/ming_logo2

kernel.img: loader $(OBJ_FILES) ../resources/ming_logo2.raw
	$(ARM-GNU)-ld $(OBJ_FILES) -T loader -o boot.elf
	$(ARM-GNU)-objdump -D boot.elf > boot.list
#	$(ARM-GNU)-objcopy boot.elf -O ihex boot.hex
	$(ARM-GNU)-objcopy boot.elf -S -O binary kernel.img


#------------------------------------------------------------------------------
# Rust
#------------------------------------------------------------------------------

hello.o: hello.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c hello.bc
	$(ARM-GNU)-objdump -D hello.o > hello.list

hello.bc: hello.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc hello.rs

video.o: video.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c video.bc
	$(ARM-GNU)-objdump -D video.o > video.list

video.bc: video.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc video.rs





#------------------------------------------------------------------------------
# Running
#------------------------------------------------------------------------------

run: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -kernel kernel.img

debug: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -s -S -kernel kernel.img

debugger:
	$(ARM-GNU)-gdb -ex "target remote localhost:1234" 
