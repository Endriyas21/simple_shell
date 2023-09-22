#include "shell.h"

/**
 * customEputs - Prints an input string to stderr.
 * @string: The string to be printed.
 *
 * Return: Nothing.
 */
void customEputs(const char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		customEputchar(string[index]);
		index++;
	}
}

/**
 * customEputchar - Writes the character c to stderr.
 * @character: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int customEputchar(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * customPutFileDescriptor - Writes the character c to the given file descriptor.
 * @character: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int customPutFileDescriptor(char character, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * customPutsFileDescriptor - Prints an input string to the given file descriptor.
 * @string: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int customPutsFileDescriptor(char *string, int fd)
{
	int index = 0;

	if (!string)
		return (0);
	while (*string)
	{
		index += customPutFileDescriptor(*string++, fd);
	}
	return (index);
}
