#include "main.h"

/************ PRINT POINTER ************/
/**
 * print_pointer-Prints the value of a pointer variable
 * @type: List a of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	char extra_c = 0, pad = ' ';
	int ind = BUFF_SIZE - 2, length = 2, pad_start = 1; /* length=2, for '0x' */
	unsigned long num_adars;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(type, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	bufr[BUFF_SIZE - 1] = '\0';
	UNUSED(prec);

	num_adars = (unsigned long)addrs;

	while (num_adars > 0)
	{
		bufr[ind--] = map_to[num_adars % 16];
		num_adars /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &bufr[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(bufr, ind, length,
		width, flags, pad, extra_c, pad_start));
}

/************* PRINT NON PRINTABLE ***********/
/**
 * print_non_printable-Prints ascii codes in hexa of non printable chars
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(type, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			bufr[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], bufr, i + offset);

		i++;
	}

	bufr[i + offset] = '\0';

	return (write(1, bufr, i + offset));
}

/************* PRINT REVERSE *****************/
/**
 * print_reverse-Prints reverse string.
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(bufr);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(type, char *);

	if (str == NULL)
	{
		UNUSED(prec);

		str = ")Null(";
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
/************* PRINT A STRING IN ROT13 **************/
/**
 * print_rot13string-Print a string in rot13.
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(type, char *);
	UNUSED(bufr);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
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
