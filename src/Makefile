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

OBJ_FILES = start.o boot.o memset.o video.o serial.o

RUSTC = rustc
CLANG = clang-mp-3.6

kernel: kernel.img

all:  kernel

clean:
	rm -f *.o *.bin *.hex *.elf *.list *.img *.bc *.clang.s

start.o: start.s ../resources/ming_logo2.raw
	$(ARM-GNU)-gcc $(COPTS) -c start.s -o start.o

#boot.o: boot.c start.h
#	$(ARM-GNU)-gcc $(COPTS) -c boot.c -o boot.o

memset.o: memset.s
	$(ARM-GNU)-gcc $(COPTS) -c memset.s -o memset.o

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

serial.o: serial.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c serial.bc
	$(ARM-GNU)-objdump -D serial.o > serial.list

serial.bc: serial.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc serial.rs -L ./
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o serial.ll --emit ir serial.rs -L ./


video.o: video.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c video.bc
	$(ARM-GNU)-objdump -D video.o > video.list

video.bc: video.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc video.rs -L ./


boot.o: boot.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c boot.bc
	$(ARM-GNU)-objdump -D boot.o > boot.list

boot.bc: boot.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc boot.rs -L ./





#------------------------------------------------------------------------------
# Running
#------------------------------------------------------------------------------

run: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -kernel kernel.img

debug: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -s -S -kernel kernel.img

debugger:
	$(ARM-GNU)-gdb -ex "target remote localhost:1234" 
