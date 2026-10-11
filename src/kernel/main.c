#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../screen/terminal.h"
#include "../vga/vga.h"
#include "../keyboard/keyboard.h"

void	kernel_main(void)
{
	char c;
	terminal_initialize();
	terminal_putentryat('4', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK), (TERM_WIDTH / 2) - 1, TERM_HEIGHT / 2);
	terminal_putentryat('2', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK), (TERM_WIDTH / 2), TERM_HEIGHT / 2);
	select_terminal(1);
	terminal_putentryat('4', vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK), (TERM_WIDTH / 2) - 1, TERM_HEIGHT / 2);
	terminal_putentryat('2', vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK), (TERM_WIDTH / 2), TERM_HEIGHT / 2);
	select_terminal(2);
	terminal_putentryat('4', vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK), (TERM_WIDTH / 2) - 1, TERM_HEIGHT / 2);
	terminal_putentryat('2', vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK), (TERM_WIDTH / 2), TERM_HEIGHT / 2);
	select_terminal(0);
	while (true)
	{
		c = poll_keyboard();
		terminal_putchar(c);
	}
}
