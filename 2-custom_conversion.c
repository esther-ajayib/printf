#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a format.
 * @format: The format string
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char *str;
	int num;
	unsigned int u_num;

	va_start(args, format);

	while (format && *format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					_putchar(va_arg(args, int));
					count++;
					break;
				case 's':
					str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";
					while (*str)
					{
						_putchar(*str);
						str++;
						count++;
					}
					break;
				case '%':
					_putchar('%');
					count++;
					break;
				case 'd':
				case 'i':
					num = va_arg(args, int);
					count += print_number(num);
					break;
				case 'b':
					u_num = va_arg(args, unsigned int);
					count += print_binary(u_num);
					break;
				default:
					_putchar('%');
					count++;
					_putchar(*format);
					count++;
					break;
			}
		}
		else
		{
			_putchar(*format);
			count++;
		}
		format++;
	}

	va_end(args);

	return (count);
}

/**
 * print_number - Prints a number
 * @num: The number to print
 *
 * Return: The number of characters printed
 */
int print_number(int num)
{
	int count = 0;
	int divisor = 1;

	if (num < 0)
	{
		_putchar('-');
		count++;
		num *= -1;
	}

	while (divisor <= num / 10)
		divisor *= 10;

	while (divisor >= 1)
	{
		_putchar('0' + (num / divisor));
		count++;
		num %= divisor;
		divisor /= 10;
	}

	return (count);
}

/**
 * print_binary - Prints an unsigned integer in binary format
 * @num: The unsigned integer to print in binary
 *
 * Return: The number of characters printed
 */
int print_binary(unsigned int num)
{
	int count = 0;
	unsigned int mask = 1 << ((sizeof(unsigned int) * 8) - 1);

	while (mask)
	{
		_putchar((num & mask) ? '1' : '0');
		count++;
		mask >>= 1;
	}

	return (count);
}
