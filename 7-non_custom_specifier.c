#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <ctype.h>
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
				i = 0;

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
					buffer[i++] = '0';
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
			else if (*format == 'S')
			{
				char *s = va_arg(args, char *);
				i = 0;

				while (s && s[i])
				{
					if (s[i] < 32 || s[i] >= 127)
					{
						_putchar('\\');
						_putchar('x');
						_putchar((s[i] >> 4) + '0');
						_putchar((s[i] & 0xF) + '0');
						count += 4;
					}
					else
					{
						_putchar(s[i]);
						count++;
					}
					i++;
				}
			}
			else if (*format == 'p')
			{
				void *ptr = va_arg(args, void *);
				unsigned long int address = (unsigned long int)ptr;
				_putchar('0');
				_putchar('x');
				count += 2;

				if (address == 0)
				{
					_putchar('0');
					count++;
				}
				else
				{
					for (i = 0; address != 0; i++)
					{
						buffer[i] = hex_digits[address % 16];
						address /= 16;
					}

					for (j = i - 1; j >= 0; j--)
					{
						_putchar(buffer[j]);
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
