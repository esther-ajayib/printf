#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <ctype.h>

/**
 * _puts - Writes a string to stdout
 * @str: The string to write
 *
 * Return: On success, returns the number of characters written.
 * On error, returns -1.
 */
int _puts(char *str)
{
	int i = 0;
	int count = 0;

	while (str[i])
	{
		_putchar(str[i]);
		count++;
		i++;
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
	char buffer[1024];
	int count = 0;
	int buffer_index = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			buffer[buffer_index] = *format;
			buffer_index++;
			count++;
			if (buffer_index == 1024)
			{
				count += _puts(buffer);
				buffer_index = 0;
			}
		}
		else
		{
			format++;
			if (*format == '\0')
				break;

			if (*format == '%')
			{
				buffer[buffer_index] = '%';
				buffer_index++;
				count++;
				if (buffer_index == 1024)
				{
					count += _puts(buffer);
					buffer_index = 0;
				}
			}
			else if (*format == 'c')
			{
				int c = va_arg(args, int);
				buffer[buffer_index] = c;
				buffer_index++;
				count++;
				if (buffer_index == 1024)
				{
					count += _puts(buffer);
					buffer_index = 0;
				}
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *);
				int i = 0;

				while (s && s[i])
				{
					buffer[buffer_index] = s[i];
					buffer_index++;
					count++;
					if (buffer_index == 1024)
					{
						count += _puts(buffer);
						buffer_index = 0;
					}
					i++;
				}
			}
			else if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				int div = 1;

				if (num < 0)
				{
					buffer[buffer_index] = '-';
					buffer_index++;
					count++;
					num = -num;
				}

				while (num / div > 9)
					div *= 10;

				while (div != 0)
				{
					buffer[buffer_index] = num / div % 10 + '0';
					buffer_index++;
					count++;
					if (buffer_index == 1024)
					{
						count += _puts(buffer);
						buffer_index = 0;
					}
					div /= 10;
				}
			}
			else if (*format == 'b')
			{
				unsigned int num = va_arg(args, unsigned int);
				char binary[1024];
 				int i, j;

				for (i = 0; num > 0; i++)
				{
					binary[i] = num % 2;
					num /= 2;
				}

				for (j = i - 1; j >= 0; j--)
				{
					binary[buffer_index++] = binary[j] + '0';
					count++;

					if (buffer_index == 1024)
					{
						write(1, binary, buffer_index);
						buffer_index = 0;
					}
				}

				if (buffer_index > 0)
					write(1, binary, buffer_index);
			}
			else if (*format == 'u')
			{
				unsigned int num = va_arg(args, unsigned int);
                                unsigned int div = 1;

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
				unsigned int num = va_arg(args, unsigned int);
				unsigned int oct = 0;
				unsigned int mult = 1;

				while (num > 0)
				{
					oct += (num % 8) * mult;
					num /= 8;
					mult *= 10;
				}

				while (mult > 1)
				{
					buffer[buffer_index] = oct / (mult / 10) + '0';
					buffer_index++;
					count++;
					if (buffer_index == 1024)
					{
						count += _puts(buffer);
						buffer_index = 0;
					}
					mult /= 10;
				}

			}
			else if (*format == 'x' || *format == 'X')
			{
				unsigned int num = va_arg(args, unsigned int);
				int rem;
				char hex[100];
				int i = 0;

				while (num != 0)
				{
					rem = num % 16;
					if (rem < 10)
						hex[i++] = rem + 48;
					else
						hex[i++] = rem + 55;
					num /= 16;
				}

				while (i > 0)
				{
					buffer[buffer_index] = hex[i - 1];
					buffer_index++;
					count++;
					if (buffer_index == 1024)
					{
						count += _puts(buffer);
						buffer_index = 0;
					}
					i--;
				}
			}
		}

		format++;
	}

	va_end(args);
	return (count);
}
