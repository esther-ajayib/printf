#include "main.h"
#include <string.h>

/**
 * print_plus_space_flags - Prints the '+' and ' ' flags if needed
 *
 * @flags: The flags string
 * Return: The number of characters printed
 */
int print_plus_space_flags(const char *flags)
{
	int count = 0;

	while (*flags)
	{
		if (*flags == '+')
			count += _putchar('+');
		else if (*flags == ' ')
			count += _putchar(' ');

		flags++;
	}

	return (count);
}

/**
 * _printf - Prints output according to a format
 *
 * @format: The format string
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	const char *flags = "+ ";

	va_start(args, format);

	while (format && *format)
	{
		if (*format == '%')
		{
			format++;

			if (*format == '\0')
				break;

			if (strchr(flags, *format))
				count += print_plus_space_flags(format);
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
