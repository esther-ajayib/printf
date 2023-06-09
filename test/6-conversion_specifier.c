#include "main.h"

/**
 * print_address - Prints the address of a pointer
 * @args: The va_list argument containing the pointer
 *
 * Return: The number of characters printed
 */
int print_address(va_list args)
{
	void *ptr = va_arg(args, void *);

	if (!ptr)
		return (_printf("(nil)"));

	return (_printf("0x%lx", (unsigned long)ptr));
}

/**
 * get_custom_specifier - Retrieves the corresponding print function for a custom specifier
 * @specifier: The custom specifier character
 *
 * Return: A pointer to the corresponding print function, or NULL if not found
 */
int (*get_custom_specifier(char specifier))(va_list)
{
	if (specifier == 'p')
		return (print_address);

	return (NULL);
}

/**
 * _printf - Prints formatted output to stdout
 * @format: The format string
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;
	int (*f)(va_list);

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			f = get_custom_specifier(format[i]);
			if (f != NULL)
				count += f(args);
			else
				count += _putchar('%') + _putchar(format[i]);
		}
		else
		{
			count += _putchar(format[i]);
		}
		i++;
	}

	va_end(args);

	return (count);
}

