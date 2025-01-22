#include "main.h"
#include <unistd.h>
#include <stdarg.h>
int _putchar(char c)
{
return (write(1, &c, 1));
}
int print_char(va_list args)
{
char c = va_arg(args, int);
return (_putchar(c));
}
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
int print_number(int n)
{
int count = 0;
if (n < 0)
{
count += _putchar('-');
n = -n;
}
if (n / 10)
count += print_number(n / 10);
count += _putchar(n % 10 + '0');
return (count);
}
int handle_specifier(char format, va_list args)
{
int count = 0;
if (format == 'c')
count += print_char(args);
else if (format == 's')
count += print_string(args);
else if (format == '%')
count += _putchar('%);
else if (format == 'd' || format == 'i')
count += print_number(va_arg(args, int));
else
{
count += _putchar('%');
count += _putchar(format);
}
return (count);
}
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
count += handle_specifier(format[i], args);
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

