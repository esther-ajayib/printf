#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a format.
 * @format: A character string containing zero or more directives.
 *
 * Return: The number of characters printed (excluding the null byte used to end output to strings).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int num;
    unsigned int u_num;
    char c;
    char *str;

    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            write(1, format, 1);
            count++;
        }
        else
        {
            format++;
            switch (*format)
            {
                case 'c':
                    c = (char)va_arg(args, int);
                    write(1, &c, 1);
                    count++;
                    break;
                case 's':
                    str = va_arg(args, char *);
                    while (*str)
                    {
                        write(1, str, 1);
                        str++;
                        count++;
                    }
                    break;
                case '%':
                    write(1, "%", 1);
                    count++;
                    break;
                case 'd':
                case 'i':
                    num = va_arg(args, int);
                    if (num < 0)
                    {
                        write(1, "-", 1);
                        count++;
                        num = -num;
                    }
                    count += print_number(num);
                    break;
                case 'b':
                    u_num = va_arg(args, unsigned int);
                    count += print_binary(u_num);
                    break;
                default:
                    write(1, format - 1, 2);
                    count += 2;
                    break;
            }
        }

        format++;
    }

    va_end(args);

    return count;
}

/**
 * print_number - Prints a number to stdout.
 * @num: The number to be printed.
 *
 * Return: The number of characters printed.
 */
int print_number(int num)
{
    int count = 0;

    if (num / 10)
        count += print_number(num / 10);

    char digit = '0' + (num % 10);
    write(1, &digit, 1);
    count++;

    return count;
}

/**
 * print_binary - Prints an unsigned integer as binary to stdout.
 * @num: The unsigned integer to be printed as binary.
 *
 * Return: The number of characters printed.
 */
int print_binary(unsigned int num)
{
    int count = 0;

    if (num / 2)
        count += print_binary(num / 2);

    char digit = '0' + (num % 2);
    write(1, &digit, 1);
    count++;

    return count;
}
