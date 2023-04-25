#include "main.h"

void print_bufr(char bufr[], int *bf_ind);

/**
 * _printf-Printf function
 * @formt: format.
 * Return: printed_ chars.
 */
int _printf(const char *formt, ...)
{
	int i, printd_ = 0, printd__chars = 0;
	int flags, width, prec, size, bf_ind = 0;
	va_list list;
	char bufr[BUFF_SIZE];

	if (formt == NULL)
		return (-1);

	va_start(list, formt);

	for (i = 0; formt && formt[i] != '\0'; i++)
	{
		if (formt[i] != '%')
		{
			bufr[bf_ind++] = formt[i];
			if (bf_ind == BUFF_SIZE)
				print_bufr(bufr, &bf_ind);
			/* write(1, &formt[i], 1);*/
			printd__chars++;
		}
		else
		{
			print_bufr(bufr, &bf_ind);
			flags = get_flags(formt, &i);
			width = get_width(formt, &i, list);
			prec = get_prec(formt, &i, list);
			size = get_size(formt, &i);
			++i;
			printd_ = handle_print(formt, &i, list, bufr,
				flags, width, prec, size);
			if (printd_ == -1)
				return (-1);
			printd__chars += printd_;
		}
	}

	print_bufr(bufr, &bf_ind);

	va_end(list);

	return (printd__chars);
}

/**
 * print_bufr-Prints the contents of the bufr if it exist
 * @bufr: Array of chars
 * @bf_ind: Index at which to add next char, represents the length.
 */
void print_bufr(char bufr[], int *bf_ind)
{
	if (*bf_ind > 0)
		write(1, &bufr[0], *bf_ind);

	*bf_ind = 0;
}
