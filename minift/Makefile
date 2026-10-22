CC=i686-elf-gcc
CFLAGS=-Wall -Wextra -Werror -std=gnu99 -ffreestanding -c
SOURCEFILES=src/str/ft_atoi.c src/mem/ft_bzero.c src/cond/ft_isalnum.c \
	    src/cond/ft_isalpha.c src/cond/ft_isascii.c src/cond/ft_isdigit.c \
	    src/cond/ft_isprint.c src/mem/ft_memchr.c \
	    src/mem/ft_memcmp.c src/mem/ft_memcpy.c src/mem/ft_memmove.c src/mem/ft_memset.c \
	    src/printf/ft_printf.c \
	    src/str/ft_strchr.c src/str/ft_striteri.c \
	    src/str/ft_strlcat.c src/str/ft_strlcpy.c \
	    src/str/ft_strlen.c src/str/ft_strncmp.c \
	    src/str/ft_strnstr.c src/str/ft_strrchr.c \
	    src/str/ft_tolower.c src/str/ft_toupper.c \
	    src/printf/printhex.c \
	    src/printf/printnumbers.c src/printf/printptr.c
OBJECTS=$(patsubst src/%.c,objects/%.o,$(SOURCEFILES))
OBJDIR=objects
NAME=libft.a

all: $(OBJECTS) $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs libft.a $(OBJECTS)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
