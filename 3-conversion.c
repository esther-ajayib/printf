#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout
 * @c: The character to write
 *
 * Return: On success, returns the number of characters written.
 * On error, returns -1.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
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
					_putchar(oct / (mult / 10) + '0');
					count++;
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
					

