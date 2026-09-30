#ifndef CONSTS_H
# define CONSTS_H

# define TERM_WIDTH 80
# define TERM_HEIGHT 25
# define VGA_MEMORY 0xB8000 // BIOS VGA Text mem address
# define GET_SCREENPOS(x, y) { y * TERM_WIDTH + x }

#endif // CONSTS_H
