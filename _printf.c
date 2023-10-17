#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - Function that print passed params
 * @format: output format
 * Return: Always 0
 */

int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	int c;
	const char *str = va_arg(args, const char *);
	const char *null_str = "(null)";

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			putchar(*format);
			printed_chars++;
		}
		else
		{
			format++;
			switch (*format)
			{
				case 'c':
				{
					c = va_arg(args, int);
					putchar(c);
					printed_chars++;
					break;
				}
				case 's':
				{
					if (str)
					{
						while (*str)
						{
							putchar(*str);
							printed_chars++;
							str++;
						}
					}
					else
					{
						while (*null_str)
						{
							putchar(*null_str);
							printed_chars++;
							null_str++;
						}
					}
					break;
				}
				case '%':
					putchar('%');
					printed_chars++;
					break;
				default:
					putchar('%');
					putchar(*format);
					printed_chars += 2;
					break;
			}
		}
		format++;
	}

	va_end(args);
	return (printed_chars);
}
