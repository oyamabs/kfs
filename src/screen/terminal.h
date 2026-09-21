#ifndef TERMINAL_H
# define TERMINAL_H

# include "../consts.h"
# include <stddef.h>
# include <stdint.h>

struct s_terminal {
	size_t row;
	size_t col;
	uint8_t color;
	uint16_t *buffer;
};

void	terminal_initialize(void);
void	terminal_setcolor(uint8_t color);
void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void	terminal_putchar(char c);

#endif // TERMINAL_H
