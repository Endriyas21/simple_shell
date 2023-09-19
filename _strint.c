#include "shell.h"

	/**
	 * interactive - shows true if as long as the shell is in dynamic
	 * @info: for structing addresses
	 *
	 * Return: when true shows 1 if not the case, 0
	 */
	int
	interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_dt - for checking whether the character is delimeter or not
 * @c: charac checking
 * @dlm: for delimeter str
 * Return: when true shows 1 if not the case, 0
 */
int is_dt(char c, char *dlm)
{
	while (*dlm)
		if (*dlm++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha -  alphabet char checker
 * @a: char for input
 * Return: when true shows 1 if not the case, 0
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _strint - change string to int
 * @b: the string to be converted
 * Return: when true shows for converted numbers 1 if not the case, 0
 */

int _strint(char *b)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; b[i] != '\0' && flag != 2; i++)
	{
		if (b[i] == '-')
			sign *= -1;

		if (b[i] >= '0' && b[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (b[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
