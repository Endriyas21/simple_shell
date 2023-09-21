#include "shell.h"

/**
 * customStrCopy - Copies a string up to a specified number of characters.
 * @destination: The destination string to copy to.
 * @source: The source string.
 * @numChars: The number of characters to copy.
 * Return: The concatenated string.
 */
char *customStrCopy(char *destination, char *source, int numChars)
{
	int indexSrc, indexDest;
	char *result = destination;

	indexSrc = 0;
	while (source[indexSrc] != '\0' && indexSrc < numChars - 1)
	{
		destination[indexSrc] = source[indexSrc];
		indexSrc++;
	}
	if (indexSrc < numChars)
	{
		indexDest = indexSrc;
		while (indexDest < numChars)
		{
			destination[indexDest] = '\0';
			indexDest++;
		}
	}
	return (result);
}

/**
 * customStrConcat - Concatenates two strings up to a specified number of bytes.
 * @destination: The first string.
 * @source: The second string.
 * @numBytes: The maximum number of bytes to concatenate.
 * Return: The concatenated string.
 */
char *customStrConcat(char *destination, char *source, int numBytes)
{
	int indexDest, indexSrc;
	char *result = destination;

	indexDest = 0;
	while (destination[indexDest] != '\0')
		indexDest++;
	indexSrc = 0;
	while (source[indexSrc] != '\0' && indexSrc < numBytes)
	{
		destination[indexDest] = source[indexSrc];
		indexDest++;
		indexSrc++;
	}
	if (indexSrc < numBytes)
		destination[indexDest] = '\0';
	return (result);
}

/**
 * customStrFindChar - Locates a character in a string.
 * @string: The string to search.
 * @character: The character to find.
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *customStrFindChar(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
