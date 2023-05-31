#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

int _putchar(char c);
int _printf(const char *format, ...);
int print_number(unsigned int n, int base, int uppercase);
int print_address(va_list args);
int print_binary(unsigned int num);

#endif /* MAIN_H */
