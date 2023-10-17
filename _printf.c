#include <stdio.h>
#include <stdarg.h>
#include "main.h"

// Function to perform cleanup after _printf
void performCleanup(va_list arguments, buffer_t *output);

// Process and print formatted output
int processFormattedString(const char *format, va_list arguments, buffer_t *output);

// Custom printf function
int customPrintf(const char *format, ...);

void performCleanup(va_list arguments, buffer_t *output)
{
    // Implementation of cleanup
    va_end(arguments);
    write(1, output->start, output->len);
    free_buffer(output);
}

int processFormattedString(const char *format, va_list arguments, buffer_t *output)
{
    // Implementation of processFormattedString
    int index, width, precision, result = 0;
    char temp;
    unsigned char flags, length;
    unsigned int (*specifierHandler)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

    for (index = 0; *(format + index); index++)
    {
        length = 0;
        if (*(format + index) == '%')
        {
            temp = 0;
            flags = handle_flags(format + index + 1, &temp);
            width = handle_width(arguments, format + index + temp + 1, &temp);
            precision = handle_precision(arguments, format + index + temp + 1, &temp);
            length = handle_length(format + index + temp + 1, &temp);

            specifierHandler = handle_specifiers(format + index + temp + 1);
            if (specifierHandler != NULL)
            {
                index += temp + 1;
                result += specifierHandler(arguments, output, flags, width, precision, length);
                continue;
            }
            else if (*(format + index + temp + 1) == '\0')
            {
                result = -1;
                break;
            }
        }
        result += _memcpy(output, (format + index), 1);
        index += (length != 0) ? 1 : 0;
    }
    performCleanup(arguments, output);
    return result;
}

int customPrintf(const char *format, ...)
{
    buffer_t *outputBuffer;
    va_list argumentList;
    int returnValue;

    if (format == NULL)
        return -1;

    outputBuffer = init_buffer();
    if (outputBuffer == NULL)
        return -1;

    va_start(argumentList, format);

    returnValue = processFormattedString(format, argumentList, outputBuffer);

    return returnValue;
}

