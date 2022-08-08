#include "main.h"

/**
 * get_width - calculates the width for printing
 * @format: formatted string to print the argument
 * @i: list of arguments
 * @list: arguments
 * Return: width
 */

int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += fornat[curr_i] - '0';
		}
		else if *(formatt[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(int, list);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;

	return (width);
}
