#include "../vga/vga.h"
#include "terminal.h"

struct s_terminal term;

void	terminal_initialize()
{
	term.buffer = (uint16_t*)VGA_MEMORY;
	term.row = 0;
	term.col = 0;
	term.color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

	for (size_t y = 0; y < TERM_HEIGHT; y++)
	{
		for (size_t x = 0; x < TERM_WIDTH; x++)
		{
			size_t index = y * TERM_WIDTH + x;
			term.buffer[index] = vga_entry(' ', term.color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	term.color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	size_t index = y * TERM_WIDTH + x;
	term.buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, term.color, term.col, term.row);
	if (++term.col == TERM_WIDTH)
	{
		term.col = 0;
		if (++term.row == TERM_HEIGHT)
			term.row = 0;
	}

}
