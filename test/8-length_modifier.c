#include "main.h"

/**
 * print_number - Prints a number according to the length modifier
 *
 * @args: The va_list containing the number argument
 * @length_modifier: The length modifier ('l' or 'h')
 * @specifier: The conversion specifier ('d', 'i', 'u', 'o', 'x', or 'X')
 * Return: The number of characters printed
 */
int print_number(va_list args, char length_modifier, char specifier)
{
        long int num;
        int count = 0;

        if (length_modifier == 'l')
                num = va_arg(args, long int);
        else if (length_modifier == 'h')
        {
                if (specifier == 'u')
                        num = (unsigned short)va_arg(args, unsigned int);
                else
                        num = (short)va_arg(args, int);
        }
        else
                num = va_arg(args, int);

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
        char length_modifier = '\0';

        va_start(args, format);

        while (format && *format)
        {
                if (*format == '%')
                {
                        format++;

                        if (*format == '\0')
                                break;

                        if (*format == 'l' || *format == 'h')
                                length_modifier = *format++;
                        else
                                length_modifier = '\0';

                        if (strchr("diuoxX", *format))
                                count += print_number(args, length_modifier, *format);
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

