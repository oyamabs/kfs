#ifndef TYPES_H
# define TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/// VGA

typedef enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
}	t_vga_color;

/// TERMINAL

struct s_terminal {
	size_t row;
	size_t col;
	uint8_t color;
	uint16_t *buffer;
};

/// KEYBOARD
struct s_kbd_mod {
	bool	caps_lock;
	bool	shift;
	bool	l_alt;
	bool	r_alt;
	bool	ctrl;
};

  // Scan codes set 1 (https://wiki.osdev.org/PS/2_Keyboard#Scan_Code_Set_1)
    // Please note that F11 is separated from the rest for historical reasons such as the introduction of the 101-key IBM model M keybaord
    // Also note that KDB_KEYPAD_DOT (0x53) and F11 (0x57) are separated, these keys still 'exist' today but aren't usable today as those features are removed from modern keyboards
typedef enum e_kbd_scancode {
	KBD_UNDEFINED = 0,
	KBD_ESCAPE = 0x01, KBD_1, KBD_2, KBD_3, KBD_4, KBD_5, KBD_6, KBD_7, KBD_8, KBD_9, KBD_0, KBD_MINUS, KBD_EQUAL, KBD_BACKSPACE,
	KBD_TAB = 0x0F, KBD_Q, KBD_W, KBD_E, KBD_R, KBD_T, KBD_Y, KBD_U, KBD_I, KBD_O, KBD_P, KBD_OPEN_BRACKET, KBD_CLOSE_BRACKET, KBD_ENTER,
	KBD_L_CTRL = 0x1D, KBD_A, KBD_S, KBD_D, KBD_F, KBD_G, KBD_H, KBD_J, KBD_K, KBD_L, KBD_SEMICOLON, KBD_QUOTE, KBD_BACKTICK,
	KBD_L_SHIFT = 0x2A, KBD_BACKSLASH, KBD_Z, KBD_X, KBD_C, KBD_V, KBD_B, KBD_N, KBD_M, KBD_COMMA, KBD_DOT, KBD_SLASH, KBD_R_SHIFT,
	KBD_KEYPAD_STAR = 0x37, KBD_L_ALT, KBD_SPACE, KBD_CAPS_LOCK, KBD_F1, KBD_F2, KBD_F3, KBD_F4, KBD_F5, KBD_F6, KBD_F7, KBD_F8, KBD_F9, KBD_F10,
	KBD_NUM_LOCK = 0x45, KBD_SCROLL_LOCK, KBD_KEYPAD_7, KBD_KEYPAD_8, KBD_KEYPAD_9, KBD_KEYPAD_MINUS, KBD_KEYPAD_4, KBD_KEYPAD_5, KBD_KEYPAD_6, KBD_KEYPAD_PLUS, KBD_KEYPAD_1, KBD_KEYPAD_2, KBD_KEYPAD_3, KBD_KEYPAD_0, KBD_KEYPAD_DOT,
	KBD_F11 = 0x57, KBD_F12
}	t_kbd_scancode;

enum e_kbd_layout_flags {
	FLAG_CAPS_LOCK = 0x1, FLAG_TOGGLE = 0x2
};

// used for layouts
typedef struct s_kbd_entry {
	uint8_t mode;
	t_kbd_scancode scancode;
	char normal;
	char shift;
	char alt;
}	t_kbd_entry;

typedef struct s_kbd_event {
	struct s_kbd_mod modifier;
	t_kbd_entry entry;
	char ascii;
}	t_kbd_event;


#endif // TYPES_H
