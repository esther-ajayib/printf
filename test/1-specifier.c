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
			else if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				int div = 1;

				if (num < 0)
				{
					_putchar('-');
					count++;
					num = -num;
				}

				while (num / div > 9)
					div *= 10;

				while (div != 0)
				{
					_putchar(num / div % 10 + '0');
					count++;
					div /= 10;
				}
			}
		}

		format++;
	}

	va_end(args);
	return (count);
}
