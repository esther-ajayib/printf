#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Prints output according to a format.
 * @format: The format string
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			_putchar(*format);
			count++;
		}
		else
		{
			format++;
			if (*format == '\0')
				break;

			if (*format == '%')
			{
				_putchar('%');
				count++;
			}
			else if (*format == 'c')
			{
				int c = va_arg(args, int);
				_putchar(c);
				count++;
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *);
				int i = 0;

				while (s && s[i])
				{
					_putchar(s[i]);
					count++;
					i++;
				}
			}
		}

		format++;
	}

	va_end(args);
	return (count);
}
