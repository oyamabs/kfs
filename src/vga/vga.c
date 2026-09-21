#include "vga.h"

uint8_t	vga_entry_color(t_vga_color fg, t_vga_color bg)
{
	return (fg | bg << 4);
}

uint16_t	vga_entry(unsigned char c, uint8_t color)
{
	return c | color << 8;
}

