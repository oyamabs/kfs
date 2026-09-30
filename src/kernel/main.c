#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "../screen/terminal.h"
#include "../keyboard/keyboard.h"
#include "io.h"

void	kernel_main(void)
{
	terminal_initialize();
	terminal_putstr("42");
	poll_keyboard();
}
