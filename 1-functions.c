#include "main.h"

/******PRINT UNSIGNED******/
/**
 * print_unsigned - print unsigned number
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate active flags
 * @width: get width
 * @precision: precision specifier:
 * @size: size specifier
 *
 * Return: numner of chars printed
 */

int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;

	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);


	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	} i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/******PRINT UNSIGNED OCTAL******/
/**
 * print_octal - prints an octal unsigned number
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate any active flags
 * @width: get width
 * @precision: precision specifier
 * @size: size specifier
 * Return: number of chars printed
 */

int print_octal(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	} i++;

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/******PRINT UNSIGNED HEXADECIMAL******/

/**
 * print_hex - prints a hexadecimal unsigned number
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate any active flags
 * @width: get width
 * @precision: precision specifier
 * @size: size specifier
 * Return: number of char printed
 */

int print_hex(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, flags,
				'X', width, precision, size));
}


/******PRINT UNSIGNED UPPER HEXADECIMAL******/
/**
 * print_hex_up - prints an unsigned hexadecimal number in uppercase
 *@types: a list of arguments
 *@buffer: buffer array to handle print
 *@flags: calculate active flags
 *@width: get width
 *@precision: precision specifier
 *@size: size specifier
 *Return: number of chars printed
 */

int print_hex_up(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, flags,
				'X', width, precision, size));
}

/********PRINT HEXADECIMAL IN UPPER OR LOWER CASE********/
/**
 * print_hexa - prints a hexadecimal number in upper or lower case
 * @types: a list of arguments
 * @buffer: buffer array to handle print
 * @flags: calculate active flags
 * @width: get witdth
 * @precision: precision specifier
 * @size: size specifier
 * Return: number of chars printed
 */

int print_hexa(va_list types, char buffer[], char map_to[], int flags, char flag_ch,
		int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	} i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));

}
