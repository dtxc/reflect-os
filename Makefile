C_SOURCES = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")
ASM_FILES = $(shell find asm -name "*.asm")
OBJ_FILES = ${C_SOURCES:.c=.o \
	asm/interrupt.o \
	asm/util.o \
	asm/disk_io.o}

build: os-image.img
	$(MAKE) clean

kernel.img: boot/kernel_entry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os-image.img: boot/mbr.bin kernel.img
	cat $^ > $@

run:
ifeq ($(shell test -e os-image.img && echo -n yes),yes)
	qemu-system-i386 -fda os-image.img -device isa-debug-exit,iobase=0xf4,iosize=0x04
else
	echo "os image not found. Building os-image.img..."
	$(MAKE) build 
	qemu-system-i386 -fda os-image.img -device isa-debug-exit,iobase=0xf4,iosize=0x04
endif

%.o: %.c ${HEADERS}
	gcc -I ./kernel/include -g -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -no-pie -fno-pic -Wall -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

clean:
	$(RM) $(shell find . -name "*.o")
	$(RM) kernel.img
	$(RM) boot/*.bin

compress:
ifeq ($(shell test -e os-image.img && echo -n yes),yes)
	zip -9 "os-image.zip" os-image.img
else
	$(MAKE) build
	zip -9 "os-image.zip" os-image.img
endif
