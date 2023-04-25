#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char-Prints a string
 * @c: char types.
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @prec: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char bufr[],
	int flags, int width, int prec, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	bufr[i++] = c;
	bufr[i] = '\0';

	if (width > 1)
	{
		bufr[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			bufr[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &bufr[0], 1) +
					write(1, &bufr[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &bufr[BUFF_SIZE - i - 1], width - 1) +
					write(1, &bufr[0], 1));
	}

	return (write(1, &bufr[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number-Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @prec: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char bufr[],
	int flags, int width, int prec, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, bufr, flags, width, prec,
		length, padd, extra_ch));
}

/**
 * write_num-Write a number using a bufffer
 * @ind: Index at which the number starts on the bufr
 * @bufr: bufr
 * @flags: Flags
 * @width: width
 * @prec: prec specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char bufr[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && bufr[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && bufr[ind] == '0')
		bufr[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		bufr[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			bufr[i] = padd;
		bufr[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				bufr[--ind] = extra_c;
			return (write(1, &bufr[ind], length) + write(1, &bufr[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				bufr[--ind] = extra_c;
			return (write(1, &bufr[1], i - 1) + write(1, &bufr[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				bufr[--padd_start] = extra_c;
			return (write(1, &bufr[padd_start], i - padd_start) +
				write(1, &bufr[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		bufr[--ind] = extra_c;
	return (write(1, &bufr[ind], length));
}

/**
 * write_unsgnd-Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the bufr
 * @bufr: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @prec: precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char bufr[],
	int flags, int width, int prec, int size)
{

	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (prec == 0 && ind == BUFF_SIZE - 2 && bufr[ind] == '0')
		return (0);

	if (prec > 0 && prec < length)
		padd = ' ';

	while (prec > length)
	{
		bufr[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			bufr[i] = padd;

		bufr[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &bufr[ind], length) + write(1, &bufr[0], i));
		}
		else
		{
			return (write(1, &bufr[0], i) + write(1, &bufr[ind], length));
		}
	}

	return (write(1, &bufr[ind], length));
}

/**
 * write_pointer-Write a memory address
 * @bufr: Arrays of chars
 * @ind: Index at which the number starts in the bufr
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char bufr[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			bufr[i] = padd;
		bufr[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			bufr[--ind] = 'x';
			bufr[--ind] = '0';
			if (extra_c)
				bufr[--ind] = extra_c;
			return (write(1, &bufr[ind], length) + write(1, &bufr[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			bufr[--ind] = 'x';
			bufr[--ind] = '0';
			if (extra_c)
				bufr[--ind] = extra_c;
			return (write(1, &bufr[3], i - 3) + write(1, &bufr[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				bufr[--padd_start] = extra_c;
			bufr[1] = '0';
			bufr[2] = 'x';
			return (write(1, &bufr[padd_start], i - padd_start) +
				write(1, &bufr[ind], length - (1 - padd_start) - 2));
		}
	}
	bufr[--ind] = 'x';
	bufr[--ind] = '0';
	if (extra_c)
		bufr[--ind] = extra_c;
	return (write(1, &bufr[ind], BUFF_SIZE - ind - 1));
}
