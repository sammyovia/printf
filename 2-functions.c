#include "main.h"

/******PRINT POINTER******/
/**
 * print_point - prints the value of a pointer variable
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate active flags
 * @width: get width
 * @precision: precision specifiers
 * @size: size specifiers
 * Return: number of chars printed
 */
int print_point(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, lenght = 2, padd_start = 1; /* lenght =2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		lenght++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', lenght++;
	else if (flags & F_SPACE)
		extra_c = ' ', lenght++;

	ind++;

	return (write_pointer(buffer, ind, lenght, width,
				flags, padd, extra_c, padd_start));
}

/******PRINT NON PRINTABLE******/
/**
 * print_non_printable - prints ascii code in hex of non printable chars
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate active flags
 * @width: get width
 * @precision: precision specifiers
 * @size: size specifiers
 * Return: the number of chars printed
 */

int print_non_printable(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);
		i++;
	}

	buffer[i + offset] = '\0';
	return (write(1, buffer, i + offset));
}


/******PRINT REVERSE******/
/**
 * print_rev - prints the reverse of a string
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate any active flags
 * @width: get width
 * @precision: precision specifiers
 * @size: size specifiers
 * Return: the number of chars printed
 */

int print_rev(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")NULL(";
	}

	for (i = 0; str[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}


/******PRINT A STRING IN ROT13******/
/**
 * print_rot13 - prints a string in rot13
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate active flags
 * @width: get width
 * @precision: precision specifiers
 * @size: size specifiers
 * Return: number of chars printed
 */

int print_rot13(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijkm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);


	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
