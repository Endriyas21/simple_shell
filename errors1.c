#include "shell.h"
#include <limits.h>

/**
 * customErrAtoi - Converts a string to an integer.
 * @str: The string to be converted.
 * Return: 0 if no digits found, the converted number otherwise,
 *         -1 on error.
 */
int customErrAtoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * customPrintErrorMsg - Prints an error message.
 * @info: The parameter and return info struct.
 * @errMsg: String indicating the error type.
 */
void customPrintErrorMsg(shellInfo_t *info, char *errMsg)
{
	customEputs(info->fname);
	customEputs(": ");
	customPrintDecimal(info->lineCount, STDERR_FILENO);
	customEputs(": ");
	customEputs(info->argv[0]);
	customEputs(": ");
	customEputs(errMsg);
}

/**
 * customPrintDecimal - Prints a decimal (integer) number (base 10).
 * @num: The input number.
 * @fd: The file descriptor for output.
 *
 * Return: Number of characters printed.
 */
int customPrintDecimal(int num, int fd)
{
	int (*customPutchar)(char) = customPutchar;
	int i, count = 0;
	unsigned int absValue, current;

	if (fd == STDERR_FILENO)
		customPutchar = customEputchar;
	if (num < 0)
	{
		absValue = -num;
		customPutchar('-');
		count++;
	}
	else
		absValue = num;
	current = absValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absValue / i)
		{
			customPutchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	customPutchar('0' + current);
	count++;

	return (count);
}

/**
 * customConvertNumber - Converts a number to a string representation.
 * @num: The number.
 * @base: The base for conversion.
 * @flags: Conversion flags.
 *
 * Return: The string representation of the number.
 */
char *customConvertNumber(long int num, int base, int flags)
{
	static char *charset;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	charset = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = charset[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * customRemoveComments - Replaces the first '#' character with '\0'.
 * @buffer: The string to modify.
 */
void customRemoveComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
