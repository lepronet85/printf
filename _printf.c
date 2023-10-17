#include <stdio.h>
#include <stdarg.h>
#include "main.h"

void display_output(char buffer[], int *buff_ind);

/**
 * custom_printf - Custom printf function
 * @format: format string
 * Return: Number of characters printed
 */
int custom_printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list args;
    char buffer[BUFFER_SIZE];

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFFER_SIZE)
                display_output(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            display_output(buffer, &buff_ind);
            flags = get_flags(format, &i);
            width = get_width(format, &i, args);
            precision = get_precision(format, &i, args);
            size = get_size(format, &i);
            ++i;
            printed = process_format(format, &i, args, buffer, flags, width, precision, size);
            if (printed == -1)
                return (-1);
            printed_chars += printed;
        }
    }

    display_output(buffer, &buff_ind);

    va_end(args);

    return (printed_chars);
}

/**
 * display_output - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buff_ind: Index at which to add the next character, representing the length
 */
void display_output(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

