#include "shell.h"

/**
 * isShellInteractive - Determines if the shell is in interactive mode.
 * @infoStruct: Pointer to the info_t struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int isShellInteractive(shellInfo_t *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->readDescriptor <= 2);
}
/**
 * isCharacterDelimiter - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiterString: The delimiter string.
 *
 * Return: 1 if it's a delimiter, 0 if not.
 */
int isCharacterDelimiter(char character, char *delimiterString)
{
	while (*delimiterString)
	{
		if (*delimiterString++ == character)
			return (1);
	}
	return (0);
}

/**
 * isCharacterAlphabetic - Checks if a character is alphabetic.
 * @character: The character to check.
 *
 * Return: 1 if it's alphabetic, 0 if not.
 */
int isCharacterAlphabetic(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToIntegerConverter - Converts a string to an integer.
 * @stringToConvert: The string to be converted.
 *
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int stringToIntegerConverter(char *stringToConvert)
{
	int index, sign = 1, flag = 0, resultInteger;
	unsigned int result = 0;

	for (index = 0; stringToConvert[index] != '\0' && flag != 2; index++)
	{
		if (stringToConvert[index] == '-')
			sign *= -1;

		if (stringToConvert[index] >= '0' && stringToConvert[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stringToConvert[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		resultInteger = -result;
	else
		resultInteger = result;

	return (resultInteger);
}

/**
 * customAtoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The converted integer, or -1 on error.
 */
int customAtoi(char *str)
{
	int result = 0, sign = 1, i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return -1;
		result = result * 10 + (str[i] - '0');
	}

	return sign * result;
}