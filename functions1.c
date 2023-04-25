#include "main.h"

/************* PRINT UNSIGNED NUMBER *****************/
/**
 * print_unsigned-Prints an unsigned number
 * @type: List a of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		bufr[i--] = '0';

	bufr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bufr[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, bufr, flags, width, prec, size));
}

/******** PRINT UNSIGNED NUMBER IN OCTAL  ***********/
/**
 * print_octal-Prints an unsigned number in octal notation
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		bufr[i--] = '0';

	bufr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bufr[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		bufr[i--] = '0';

	i++;

	return (write_unsgnd(0, i, bufr, flags, width, prec, size));
}

/********** PRINT UNSIGNED NUMBER IN HEXADECIMAL **********/
/**
 * print_hexadecimal-Prints an unsigned number in hexadecimal notation
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	return (print_hexa(type, "0123456789abcdef", bufr,
		flags, 'x', width, prec, size));
}

/********* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **********/
/**
 * print_hexa_upper-Prints an unsigned number in upper hexadecimal notation
 * @type: Lista of arguments
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list type, char bufr[],
	int flags, int width, int prec, int size)
{
	return (print_hexa(type, "0123456789ABCDEF", bufr,
		flags, 'X', width, prec, size));
}

/********* PRINT HEXX NUM IN LOWER OR UPPER ***********/
/**
 * print_hexa-Prints a hexadecimal number in lower or upper
 * @type: Lista of arguments
 * @map_to: Array of values to map the number to
 * @bufr: bufr array to handle print
 * @flags:  Calculates active flags
 * @flag_cal_actv: Calculates active flags
 * @width: get width
 * @prec: precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list type, char map_to[], char bufr[],
	int flags, char flag_cal_actv, int width, int prec, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		bufr[i--] = '0';

	bufr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bufr[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		bufr[i--] = flag_cal_actv;
		bufr[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, bufr, flags, width, prec, size));
}
