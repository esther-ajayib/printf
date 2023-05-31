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

	return (count);
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
	char buffer[1024];
	int buf_index = 0;
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
					if (buf_index >= 1024)
					{
						count += write(1, buffer, buf_index);
						buf_index = 0;
					}
					buffer[buf_index++] = ch;
					break;
				case 's':
					str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";
					while (*str)
					{
						if (buf_index >= 1024)
						{
							count += write(1, buffer, buf_index);
							buf_index = 0;
						}
						buffer[buf_index++] = *str++;
					}
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
					if (buf_index >= 1024)
					{
						count += write(1, buffer, buf_index);
						buf_index = 0;
					}
					buffer[buf_index++] = '%';
					break;
				default:
					if (buf_index >= 1024)
					{
						count += write(1, buffer, buf_index);
						buf_index = 0;
					}
					buffer[buf_index++] = '%';
					buffer[buf_index++] = *format;
					break;
			}
		}
		else
		{
			if (buf_index >= 1024)
			{
				count += write(1, buffer, buf_index);
				buf_index = 0;
			}
			buffer[buf_index++] = *format;
		}
		format++;
	}
	if (buf_index > 0)
		count += write(1, buffer, buf_index);

	va_end(args);

	return count;
}

