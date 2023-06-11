C_SOURCES = $(shell find . -name "*.c")
OBJ_FILES = ${C_SOURCES:.c=.o \
	boot/boot.o \
	boot/dt.o \
	interrupt/interrupt.o \
	task/process.o}

CCFLAGS = -I ./include -g -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -no-pie -fno-pic -Wall -Wextra -O2
KERNELBIN = ../build/kernel.bin
OSBIN = ../os-image.iso

build: prepare os-image.iso

os-image.iso: kernel.bin
	objcopy --only-keep-debug ../build/kernel.bin ../build/kernel.sym
	objcopy --strip-debug ../build/kernel.bin
	cd ../build && cp ./$^ ./boot/$^ && cp ../src/boot/grub.cfg ./boot/grub/grub.cfg && cd .. && \
		grub-mkrescue -o $@ build

kernel.bin: ${OBJ_FILES}
	ld -m elf_i386 -o ../build/$(notdir $@) -Tlinker.ld ../build/obj/boot.o $(shell find ../build/obj/ -name "*.o" ! -name "boot.o")

prepare:
	mkdir -p ../build/boot/grub ../build/obj

run:
ifeq ($(shell test -e $(OSBIN) && echo -n yes),yes)
	qemu-system-i386 -cdrom $(OSBIN) -soundhw pcspk -rtc base=localtime,clock=host
else
	$(MAKE) build
	qemu-system-i386 -cdrom $(OSBIN) -soundhw pcspk -rtc base=localtime,clock=host
endif

# debug:
# ifeq ($(shell test -e $(OSBIN) && echo -n yes),yes)
# 	qemu-system-i386 -cdrom $(OSBIN) -d int --no-reboot -soundhw pcspk -rtc base=localtime,clock=host
# else
# 	$(MAKE) build
# 	qemu-system-i386 -cdrom $(OSBIN) -d int --no-reboot -soundhw pcspk -rtc base=localtime,clock=host
# endif

debug:
ifeq ($(shell test -e $(OSBIN) && echo -n yes),yes)
	qemu-system-i386 -s -S -cdrom $(OSBIN)
else
	$(MAKE) build
	qemu-system-i386 -s -S -cdrom $(OSBIN)
endif

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o ../build/obj/$(notdir $@)

%.o: %.asm
	nasm $< -f elf -o ../build/obj/$(notdir $@)
	
%.o: %.psf
	objcopy -O elf32-i386 -B i386 -I binary $< ../build/obj/$(notdir $@)

clean:
	$(RM) -rf ../build $(OSBIN) $(KERNELBIN)
