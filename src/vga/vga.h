#ifndef VGA_H
# define VGA_H

# include <stdint.h>
# include "../types.h"

uint8_t	vga_entry_color(t_vga_color fg, t_vga_color bg);
uint16_t	vga_entry(unsigned char c, uint8_t color);

#endif // VGA_H
