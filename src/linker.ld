/* Entrypoint of the kernel (defined in the boot.s file) */
ENTRY(_start)

SECTIONS
{
	/* Due to how UEFI works it is strongly advised to put a 2M to be safer.
	* We could've used 1M as we'll use BIOS but UEFI and Multiboot change
	* about everything (such as the kernel being able to relocate its
	* address in more modern systems)*/
	. = 2M;

	/* First put the multiboot header, as it is required to be put very early
	   in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
