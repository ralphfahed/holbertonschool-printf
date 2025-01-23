#include <stdarg.h>
#include <unistd.h>

/**
 * print_number - Prints an integer to stdout
 * @n: The integer to print
 * Return: The number of characters printed
 */
int print_number(int n)
{
    int count = 0;
    char digit;

    if (n < 0)
    {
        count += write(1, "-", 1);
        n = -n;
    }
    if (n / 10)
        count += print_number(n / 10);
    digit = (n % 10) + '0';
    count += write(1, &digit, 1);

    return (count);
}

/**
 * _printf - Produces output according to a format
 * @format: The format string containing the characters and specifiers
 * Return: The number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0, i;

    if (!format)
        return (-1);

    va_start(args, format);
    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == '%')  /* Handle %% */
            {
                count += write(1, "%", 1);
            }
            else if (format[i] == 'c')  /* Handle %c */
            {
                char c = (char)va_arg(args, int);
                count += write(1, &c, 1);
            }
            else if (format[i] == 's')  /* Handle %s */
            {
                char *str = va_arg(args, char *);
                int len = 0;

                if (!str)
                    str = "(null)";
                while (str[len] != '\0')
                    len++;
                count += write(1, str, len);
            }
            else if (format[i] == 'd' || format[i] == 'i')  /* Handle %d and %i */
            {
                int num = va_arg(args, int);
                count += print_number(num);
            }
            else  /* Handle unknown specifiers */
            {
                count += write(1, "%", 1);
                count += write(1, &format[i], 1);
            }
        }
        else
        {
            count += write(1, &format[i], 1);
        }
    }
    va_end(args);

    return (count);
}

