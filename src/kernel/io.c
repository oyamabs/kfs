#include "io.h"

inline void outb(uint16_t port, uint8_t value)
{
	__asm__ volatile ("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

inline void outw(uint16_t port, uint16_t value)
{
	__asm__ volatile ("outw %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

inline void outl(uint16_t port, uint32_t value)
{
	__asm__ volatile ("outl %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	__asm__ volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	__asm__ volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}
