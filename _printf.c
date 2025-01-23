#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * print_char - Prints a single character
 * @args: List of arguments
 *
 * Return: Number of characters printed
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);

	return (write(1, &c, 1));
}

/**
 * print_string - Prints a string
 * @args: List of arguments
 *
 * Return: Number of characters printed
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);
	int count = 0;

	if (!str)
		str = "(null)";
	while (*str)
	{
		count += write(1, str, 1);
		str++;
	}
	return (count);
}

/**
 * print_number - Prints an integer as a string
 * @n: The integer to print
 *
 * Return: Number of characters printed
 */
int print_number(int n)
{
	char buffer[20];
	int count = 0;
	int i = 0;

	if (n == 0)
	{
		count += write(1, "0", 1);
		return (count);
	}

	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}

	/* Store digits in reverse order */
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}

	/* Write the digits in the correct order */
	while (--i >= 0)
	{
		count += write(1, &buffer[i], 1);
	}

	return (count);
}

/**
 * _printf - Produces output according to a format
 * @format: Format string containing characters and specifiers
 *
 * Return: The number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	int count = 0;
	int i = 0;
	va_list args;

	if (!format)
		return (-1);

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
				count += print_char(args);
			else if (format[i] == 's')
				count += print_string(args);
			else if (format[i] == 'd' || format[i] == 'i')
				count += print_number(va_arg(args, int));
			else if (format[i] == '%')
				count += write(1, "%", 1);
			else
			{
				count += write(1, "%", 1);
				count += write(1, &format[i], 1);
			}
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}

