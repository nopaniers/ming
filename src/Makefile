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

COPTS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -std=gnu99 -marm 


OBJ_FILES = start.o boot.o memset.o
RUST_LIBRARIES = libmorestack.a libcompiler-rt.a

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

kernel.img: loader $(OBJ_FILES) ../resources/ming_logo2.raw $(RUST_LIBRARIES)
	$(ARM-GNU)-ld $(OBJ_FILES)  -T loader -o boot.elf -lmorestack -L.
	$(ARM-GNU)-objdump -D boot.elf > boot.list
	$(ARM-GNU)-objcopy boot.elf -S -O binary kernel.img


libmorestack.a: morestack.c
	$(ARM-GNU)-gcc $(COPTS) -c morestack.c -o morestack.o
	$(ARM-GNU)-ar rcs libmorestack.a morestack.o

libcompiler-rt.a: compiler-rt.c
	$(ARM-GNU)-gcc $(COPTS) -c compiler-rt.c -o compiler-rt.o
	$(ARM-GNU)-ar rcs libcompiler-rt.a compiler-rt.o


#------------------------------------------------------------------------------
# Rust
#------------------------------------------------------------------------------

boot.o: boot.rs

%.o: %.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type=staticlib --emit obj $< -o $@ -L ./

%.a: %.rs
	$(RUSTC) -O --target arm-linux-androideabi --crate-type=staticlib $< -o $@ -L ./



#------------------------------------------------------------------------------
# Running
#------------------------------------------------------------------------------

run: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -kernel kernel.img

debug: kernel.img
	emulator -verbose -avd phone2 -shell -show-kernel -qemu -s -S -kernel kernel.img

debugger:
	$(ARM-GNU)-gdb -ex "target remote localhost:1234" 
