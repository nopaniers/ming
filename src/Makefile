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

memset.o: memset.s
	$(ARM-GNU)-gcc $(COPTS) -c memset.s -o memset.o

../resources/ming_logo2.raw: ../resources/ming_logo2.png
	../resources/convert_to_565 ../resources/ming_logo2

kernel.img: loader $(OBJ_FILES) ../resources/ming_logo2.raw
	$(ARM-GNU)-ld $(OBJ_FILES) -T loader -o boot.elf
	$(ARM-GNU)-objdump -D boot.elf > boot.list
	$(ARM-GNU)-objcopy boot.elf -S -O binary kernel.img


#------------------------------------------------------------------------------
# Rust
#------------------------------------------------------------------------------

serial.o: serial.rs
video.o: video.rs
boot.o: boot.rs

#
# A bit of a convoluted toolchain here:
#     .rs -(rustc)-> LLVM .bc -(clang)-> .o 
#
# One subtlety is that rustc and clang's LLVM versions must match. 
# Instally LLVM-3.6 was fine for me, but if you are trying to compile this in
# future, try the most recent version of each.
#

%.o: %.bc
	$(CLANG) --target=thumbv7--none-androideabi -mcpu=cortex-a8 -c $< -o $@
	$(ARM-GNU)-objdump -D $@ > $*.list

%.bc: %.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type lib -o $@ --emit bc $< -L ./



#------------------------------------------------------------------------------
# Running
#------------------------------------------------------------------------------

run: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -kernel kernel.img

debug: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -s -S -kernel kernel.img

debugger:
	$(ARM-GNU)-gdb -ex "target remote localhost:1234" 
