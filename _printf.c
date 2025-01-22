#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>  /* For INT_MIN */

/* Function prototypes */
int print_char(va_list args);
int print_string(va_list args);
int print_number(va_list args);

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: 1 on success, -1 on error.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
 * print_char - Handles the %c format specifier.
 * @args: The argument list.
 *
 * Return: The number of characters printed.
 */
int print_char(va_list args)
{
char c = va_arg(args, int);
return (_putchar(c));
}

/**
 * print_string - Handles the %s format specifier.
 * @args: The argument list.
 *
 * Return: The number of characters printed.
 */
int print_string(va_list args)
{
char *str = va_arg(args, char *);
int count = 0;

if (!str)
str = "(null)";

while (*str)
{
count += _putchar(*str);
str++;
}
return (count);
}

/**
 * print_number - Handles the %d and %i format specifiers.
 * @args: The argument list.
 *
 * Return: The number of characters printed.
 */
int print_number(va_list args)
{
int n = va_arg(args, int);
int count = 0;
char buffer[50];
int i = 0;

if (n == 0)
{
count += _putchar('0');
return (count);
}

if (n == INT_MIN)  /* Handle INT_MIN separately */
{
count += _putchar('-');
count += _putchar('2');
n = 147483648;  /* Adjust the number */
}

if (n < 0)
{
count += _putchar('-');
n = -n;
}

while (n > 0)
{
buffer[i] = (n % 10) + '0';
n /= 10;
i++;
}

while (i > 0)
{
count += _putchar(buffer[--i]);
}

return (count);
}

/**
 * handle_specifier - Handles format specifiers.
 * @format: The format string.
 * @args: The argument list.
 *
 * Return: The number of characters printed.
 */
int handle_specifier(const char *format, va_list args)
{
int count = 0;

if (*format == '%' && *(format + 1) == '\0')
{
return (count); /* No output for "%" alone */
}

switch (*format)
{
case 'c':
count += print_char(args);
break;
case 's':
count += print_string(args);
break;
case 'd':
case 'i':
count += print_number(args);
break;
case '%':
count += _putchar('%');
break;
default:
count += _putchar('%');
count += _putchar(*format);
break;
}
return (count);
}

/**
 * _printf - Produces output according to a format.
 * @format: The format string.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
va_list args;
int i = 0, count = 0;

if (!format)
return (-1);

va_start(args, format);

while (format[i])
{
if (format[i] == '%')
{
i++;
if (format[i] == '\0')
break;
count += handle_specifier(&format[i], args);
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

