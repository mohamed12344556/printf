#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmtt - Struct op
 *
 * @fmtt: The format.
 * @fn: The function associated.
 */
struct fmtt
{
	char fmtt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmtt fmtt_t - Struct op
 *
 * @fmtt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmtt fm_t;

int _printf(const char *formt, ...);
int handle_print(const char *fmtt, int *i,
va_list list, char bufr[], int flags, int width, int prec, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_string(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_percent(va_list type, char bufr[],
	int flags, int width, int prec, int size);

/* Functions to print numbers */
int print_int(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_binary(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_unsigned(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_octal(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_hexadecimal(va_list type, char bufr[],
	int flags, int width, int prec, int size);
int print_hexa_upper(va_list type, char bufr[],
	int flags, int width, int prec, int size);

int print_hexa(va_list type, char map_to[],
char bufr[], int flags, char flag_cal_actv, int width, int prec, int size);

/* Function to print non printable characters */
int print_non_printable(va_list type, char bufr[],
	int flags, int width, int prec, int size);

/* Funcion to print memory address */
int print_pointer(va_list type, char bufr[],
	int flags, int width, int prec, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *formt, int *i);
int get_width(const char *formt, int *i, va_list list);
int get_prec(const char *formt, int *i, va_list list);
int get_size(const char *formt, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list type, char bufr[],
	int flags, int width, int prec, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list type, char bufr[],
	int flags, int width, int prec, int size);

/* width handler */
int handle_write_char(char c, char bufr[],
	int flags, int width, int prec, int size);
int write_number(int is_positive, int ind, char bufr[],
	int flags, int width, int prec, int size);
int write_num(int ind, char bff[], int flags, int width, int prec,
	int length, char pad, char extra_c);
int write_pointer(char bufr[], int ind, int length,
	int width, int flags, char pad, char extra_c, int pad_start);

int write_unsgnd(int is_negative, int ind,
char bufr[],
	int flags, int width, int prec, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
