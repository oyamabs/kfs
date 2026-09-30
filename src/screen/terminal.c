#include "../vga/vga.h"
#include "terminal.h"
#include <stdbool.h>

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

bool special_chars(char c)
{
	if (c == '\n')
	{
		term.row++;
		term.col = 0;
		return true;
	}
	return false;
}

void scroll()
{
	uint16_t screen[TERM_HEIGHT][TERM_WIDTH];
	for (int y = 0; y < TERM_HEIGHT; y++)
	{
		for (int x = 0; x < TERM_WIDTH; x++)
			screen[y][x] = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
	}
	for (int y = 1; y < TERM_HEIGHT; y++)
	{
		for (int x = 0; x < TERM_WIDTH; x++)
			screen[y - 1][x] = term.buffer[y * TERM_WIDTH + x];
	}
	for (int y = 0; y < TERM_HEIGHT; y++)
	{
		for (int x = 0; x < TERM_WIDTH; x++)
			term.buffer[y * TERM_WIDTH + x] = screen[y][x];
	}
	term.row--;
}

void terminal_putchar(char c)
{
	if (special_chars(c))
		return ;
	terminal_putentryat(c, term.color, term.col, term.row);
	if (++term.col == TERM_WIDTH)
	{
		term.col = 0;
		term.row++;
	}
	if (term.row == TERM_HEIGHT)
		scroll();
}

void terminal_putstr(char *str)
{
	while (*str)
		terminal_putchar(*str++);
}
