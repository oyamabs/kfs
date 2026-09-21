#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../screen/terminal.h"

void	kernel_main(void)
{
	terminal_initialize();
	terminal_putchar('4');
	terminal_putchar('2');
}
