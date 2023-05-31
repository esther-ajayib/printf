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
 *
 * Return: The number of digits printed.
 */
int print_number(int n)
{
	int divisor = 1;
	int count = 0;

	if (n < 0)
	{
		_putchar('-');
		count++;
		n = -n;
	}

	while (n / divisor > 9)
		divisor *= 10;

	while (divisor != 0)
	{
		_putchar((n / divisor) % 10 + '0');
		divisor /= 10;
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
					count += print_number(num);
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

	return count;
}
