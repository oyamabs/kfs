#include "../vga/vga.h"
#include "terminal.h"
#include "../consts.h"
#include "../kernel/io.h"
#include <stdbool.h>
#include <stdint.h>

struct s_terminals terms;
uint16_t *vga_buffer = (uint16_t*)VGA_MEMORY;

void	terminal_initialize()
{
	for (int i = 0; i < TERM_MAXNUM; i++)
	{
		terms.term[i].row = 0;
		terms.term[i].col = 0;
		terms.term[i].color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

		for (size_t y = 0; y < TERM_HEIGHT; y++)
		{
			for (size_t x = 0; x < TERM_WIDTH; x++)
			{
				size_t index = y * TERM_WIDTH + x;
				terms.term[i].buffer[index] = vga_entry(' ', terms.term[i].color);
				vga_buffer[index] = vga_entry(' ', terms.term[i].color);
			}
		}
	}
	SELECTED_TERMINAL = 0;
}

void select_terminal(unsigned int term)
{
	SELECTED_TERMINAL = term;
	for (int y = 0; y < TERM_HEIGHT; y++)
	{
		for (int x = 0; x < TERM_WIDTH; x++)
		{
			size_t index = y * TERM_WIDTH + x;
			vga_buffer[index] = terms.term[SELECTED_TERMINAL].buffer[index];
			terminal_curpos(terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
		}
	}
}

void	terminal_curpos(uint8_t x, uint8_t y)
{
	uint16_t pos = GET_SCREENPOS(x, y);

	outb(0x3d4, 0x0f);
	outb(0x3d5, (uint8_t)(pos & 0xff));
	outb(0x3d4, 0x0e);
	outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
}

void terminal_setcolor(uint8_t color)
{
	terms.term[SELECTED_TERMINAL].color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	size_t index = y * TERM_WIDTH + x;
	terms.term[SELECTED_TERMINAL].buffer[index] = vga_entry(c, color);
	vga_buffer[index] = vga_entry(c, color);
}

bool special_chars(char c)
{
	if (c == '\n')
	{
		terms.term[SELECTED_TERMINAL].row++;
		terms.term[SELECTED_TERMINAL].col = 0;
		terminal_curpos(terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
		return true;
	}
	if (c == '\b')
	{
		if (terms.term[SELECTED_TERMINAL].col > 0)
		{
			terms.term[SELECTED_TERMINAL].col--;
			terminal_putentryat(' ', terms.term[SELECTED_TERMINAL].color, terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
		}
		if (terms.term[SELECTED_TERMINAL].col == 0 && terms.term[SELECTED_TERMINAL].row >= 1)
		{
			terms.term[SELECTED_TERMINAL].col = TERM_WIDTH;
			terms.term[SELECTED_TERMINAL].row--;
			terminal_putentryat(' ', terms.term[SELECTED_TERMINAL].color, terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
		}
		terminal_curpos(terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
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
			screen[y - 1][x] = terms.term[SELECTED_TERMINAL].buffer[y * TERM_WIDTH + x];
	}
	for (int y = 0; y < TERM_HEIGHT; y++)
	{
		for (int x = 0; x < TERM_WIDTH; x++)
			terms.term[SELECTED_TERMINAL].buffer[y * TERM_WIDTH + x] = screen[y][x];
	}
	terms.term[SELECTED_TERMINAL].row--;
}

void terminal_putchar(char c)
{
	if (special_chars(c))
		return ;
	terminal_putentryat(c, terms.term[SELECTED_TERMINAL].color, terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
	if (++terms.term[SELECTED_TERMINAL].col == TERM_WIDTH)
	{
		terms.term[SELECTED_TERMINAL].col = 0;
		terms.term[SELECTED_TERMINAL].row++;
	}
	if (terms.term[SELECTED_TERMINAL].row == TERM_HEIGHT)
		scroll();
	terminal_curpos(terms.term[SELECTED_TERMINAL].col, terms.term[SELECTED_TERMINAL].row);
}

void terminal_putstr(char *str)
{
	while (*str)
		terminal_putchar(*str++);
}
