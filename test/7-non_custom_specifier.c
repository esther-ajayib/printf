#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <ctype.h>
#include <string.h>

/**
 * print_plus_space_flags - Prints the '+' and ' ' flags if needed.
 * @flags: The flags string
 *
 * Return: The number of characters printed.
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

    return count;
}

/**
 * _printf - Prints output according to a format.
 * @format: The format string.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    const char *flags = "+# ";

    va_start(args, format);

    while (format && *format)
    {
        if (*format == '%')
        {
            format++;

            if (*format == '\0')
                break;

            if (strchr(flags, *format))
                count += print_plus_space_flags(format);
            else if (*format == 'c')
            {
                int c = va_arg(args, int);
                count += _putchar(c);
            }
            else if (*format == 's')
            {
                char *s = va_arg(args, char *);
                int i = 0;

                while (s && s[i])
                {
                    count += _putchar(s[i]);
                    i++;
                }
            }
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(args, int);
                int div = 1;

                if (num < 0)
                {
                    count += _putchar('-');
                    num = -num;
                }

                while (num / div > 9)
                    div *= 10;

                while (div != 0)
                {
                    count += _putchar(num / div % 10 + '0');
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
                    count += _putchar(num / div % 10 + '0');
                    div /= 10;
                }
            }
            else if (*format == 'o')
            {
                unsigned int num = va_arg(args, unsigned int);
                unsigned int div = 1;

                while (num / div > 7)
                    div *= 8;

                while (div != 0)
                {
                    count += _putchar(num / div % 8 + '0');
                    div /= 8;
                }
            }
            else if (*format == 'x' || *format == 'X')
            {
                unsigned int num = va_arg(args, unsigned int);
                int is_upper = (*format == 'X');
                int i = 0;
                char hex_digits[] = "0123456789abcdef";

                if (num == 0)
                {
                    count += _putchar('0');
                }
                else
                {
                    char buffer[32];

                    while (num != 0)
                    {
                        buffer[i++] = hex_digits[num % 16];
                        num /= 16;
                    }

                    while (i > 0)
                    {
			                            i--;
                        count += _putchar(is_upper ? (char)toupper(buffer[i]) : buffer[i]);
                    }
                }
            }
            else if (*format == 'S')
            {
                char *s = va_arg(args, char *);
                int i = 0;

                while (s && s[i])
                {
                    if (s[i] < 32 || s[i] >= 127)
                    {
                        count += _putchar('\\');
                        count += _putchar('x');
                        count += _putchar((s[i] >> 4) + '0');
                        count += _putchar((s[i] & 0xF) + '0');
                    }
                    else
                    {
                        count += _putchar(s[i]);
                    }
                    i++;
                }
            }
            else if (*format == 'p')
            {
                void *ptr = va_arg(args, void *);
                unsigned long int address = (unsigned long int)ptr;

                count += _putchar('0');
                count += _putchar('x');

                if (address == 0)
                {
                    count += _putchar('0');
                }
                else
                {
                    char buffer[16];
                    int i = 0;
		    int j;
                    char hex_digits[] = "0123456789abcdef";

                    while (address != 0)
                    {
                        buffer[i++] = hex_digits[address % 16];
                        address /= 16;
                    }

                    for (j = i - 1; j >= 0; j--)
                    {
                        count += _putchar(buffer[j]);
                    }
                }
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


