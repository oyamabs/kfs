CC = i686-elf-gcc
ASM = nasm -felf32
# -fno-omit-frame-pointer is to prevent malloc stacktraces from being truncated,
# see "My malloc stacktraces are too short" here:
# https://github.com/google/sanitizers/wiki/AddressSanitizer
SANITIZERS = -fsanitize=address,undefined -fno-omit-frame-pointer
ifeq ($(CFLAGS),)
	CFLAGS = -Wall -Wextra -Werror -std=gnu99 -ffreestanding
endif

ASMSRC = \
		 src/boot.s \

SOURCEFILES = \
		src/kernel/io.c \
		src/screen/terminal.c \
		src/keyboard/keyboard.c \
		src/vga/vga.c \
		src/kernel/main.c \

OBJECTS = $(SOURCEFILES:.c=.o)
ASMOBJECTS = $(ASMSRC:.s=.o)
NAME = kfs
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean fclean bonus re sane

all: $(ASMOBJECTS) $(OBJECTS) $(NAME)

-include $(DEPS)

$(NAME): $(ASMOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) -T src/linker.ld $(ASMOBJECTS) $(OBJECTS) -o $(NAME) -nostdlib -lgcc

%.o: %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) -o $*.o $*.c
	$(CC) -MM $(CFLAGS) $(IFLAGS) -MT $*.o $*.c > $*.d

%.o: %.s
	$(ASM) $*.s -o $*.o 

clean:
	find . -name '*.o' -print -delete
	find . -name '*.d' -print -delete

fclean: clean
	rm -f $(NAME)
	rm -rf iso
	rm -f $(NAME).iso

re:
	+make fclean
	+make all

vm: $(NAME)
	qemu-system-i386 -kernel kfs

makeiso: $(NAME)
	rm -rf iso
	mkdir -p iso/boot/grub
	cp $(NAME) iso/boot/$(NAME)
	sed "s/REPLACE_ME/$(NAME)/g" grub.cfg > iso/boot/grub/grub.cfg
	@if [[ "$$(uname)" == "Darwin" ]]; then \
		i686-elf-grub-mkrescue -o $(NAME).iso iso/; \
	else \
		grub-mkrescue -o $(NAME).iso iso/; \
	fi
