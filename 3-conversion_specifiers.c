#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _puts - Prints a string to stdout
 * @str: The string to be printed
 *
 * Return: The number of characters printed.
 */
int _puts(char *str)
{
	int count = 0;

	while (*str)
	{
		_putchar(*str);
		count++;
		str++;
	}

	return count;
}

/**
 * print_number - Prints a number
 * @n: The number to be printed
 * @base: The base for conversion
 * @uppercase: Flag indicating uppercase conversion for 'x' and 'X'
 *
 * Return: The number of digits printed.
 */
int print_number(unsigned int n, int base, int uppercase)
{
	unsigned int divisor = 1;
	int count = 0;

	while (n / divisor >= (unsigned int)base)
		divisor *= base;

	while (divisor != 0)
	{
		int digit = (n / divisor) % base;
		char ch;
		if (digit < 10)
			ch = '0' + digit;
		else
			ch = (uppercase ? 'A' : 'a') + digit - 10;
		_putchar(ch);
		divisor /= base;
		count++;
	}

	return count;
}

/**
 * _printf - Custom implementation of printf function
 * @format: Format string
 *
 * Return: The number of characters printed (excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char ch;
	char *str;
	int num;
	unsigned int unb;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					ch = va_arg(args, int);
					count += _putchar(ch);
					break;
				case 's':
					str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";
					count += _puts(str);
					break;
				case 'd':
				case 'i':
					num = va_arg(args, int);
					count += print_number((unsigned int)num, 10, 0);
					break;
				case 'u':
					unb = va_arg(args, unsigned int);
					count += print_number(unb, 10, 0);
					break;
				case 'o':
					unb = va_arg(args, unsigned int);
					count += print_number(unb, 8, 0);
					break;
				case 'x':
					unb = va_arg(args, unsigned int);
					count += print_number(unb, 16, 0);
					break;
				case 'X':
					unb = va_arg(args, unsigned int);
					count += print_number(unb, 16, 1);
					break;
				case '%':
					count += _putchar('%');
					break;
				default:
					count += _putchar('%');
					count += _putchar(*format);
					break;
			}
		}
		else
		{
			count += _putchar(*format);
		}

		format++;
	}

	va_end(args);

	return (count);
}
