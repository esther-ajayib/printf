#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <ctype.h>

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
	unsigned int num, div, rem;
	int binary[32];
	int i, j, is_upper;

	char hex_digits[] = "0123456789abcdef";
	char buffer[1024];

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
			else if (*format == 'b')
			{
				num = va_arg(args, unsigned int);

				for (i = 0; num > 0; i++)
				{
					binary[i] = num % 2;
					num /= 2;
				}

				for (j = i - 1; j >= 0; j--)
				{
					_putchar(binary[j] + '0');
					count++;
				}
			}
			else if (*format == 'u')
			{
				num = va_arg(args, unsigned int);
				div = 1;
				
				while (num / div > 9)
					div *= 10;

				while (div != 0)
				{
					_putchar(num / div % 10 + '0');
					count++;
					div /= 10;
				}
			}
			else if (*format == 'o')
			{
				num = va_arg(args, unsigned int);
				div = 1;

				while (num / div > 7)
					div *= 8;

				while (div != 0)
				{
					_putchar(num / div % 8 + '0');
					count++;
					div /= 8;
				}
 			}
 			else if (*format == 'x' || *format == 'X')
			{
				num = va_arg(args, unsigned int);

				is_upper = (*format == 'X');

				i = 0;

				if (num == 0)
				{
					_putchar('0');
					count++;
				}
				else
				{
					while (num != 0)
					{
						rem = num % 16;
						buffer[i++] = hex_digits[rem];
						num /= 16;
					}

					while (i > 0)
					{
						i--;
						_putchar(is_upper ? (char)toupper(buffer[i]) : buffer[i]);
						count++;
					}
				}
			}
		}

		format++;
	}

	va_end(args);
	return (count);
}
