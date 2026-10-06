#include "keyboard.h"
#include "layout.h"
#include "../types.h"
#include "../kernel/io.h"
#include "../screen/terminal.h"
#include <stdbool.h>
#include <stdint.h>

static t_kbd_event kbd = { 0 };

static char kbd_process(uint8_t scancode)
{
	static bool extended =  false;

	bool is_break = (scancode & 0x80) != 0;
	uint8_t code = scancode & 0x7f;
	switch (code)
	{
		case 0x2a: // L Shift
		case 0x36: // R Shift
			kbd.modifier.shift = !is_break;
			return 0;
		case 0x1d: // L ctrl
			kbd.modifier.ctrl = !is_break;
			return 0;
		case 0x38: // L Alt
			kbd.modifier.l_alt = !is_break;
			return 0;
		case 0x3a: // CAPS LOCK
			if (!is_break)
				kbd.modifier.caps_lock = !kbd.modifier.caps_lock;
			return 0;
	}

	if (extended) {
		extended = false;
		return 0;
	}

	if (is_break || code >= 128)
		return 0;
	
	if (kbd.modifier.l_alt)
		return 0;
	if (kbd.modifier.caps_lock || kbd.modifier.shift)
		return us_layout[code].shift;
	else
		return us_layout[code].normal;
}

char poll_keyboard()
{
	char c = 0;
	while (!c)
	{
		while (!(inb(0x64) & 1))
			__asm__ volatile ("pause");
		uint8_t scancode = inb(KBD_IO_PORT);
		c = kbd_process(scancode);
	}
	return c;
}
