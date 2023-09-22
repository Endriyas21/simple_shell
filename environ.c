#include "shell.h"
#include <stdlib.h>

/**
 * customEnv - Prints the current environment.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customEnv(shellInfo_t *shellInfo)
{
      extern char **environ;        
      char **env = environ;
      while (*env != NULL)
        {
        	printf("%s\n", *env);
        	env++;
    	}
	return (0);
}

/**
 * customGetEnvironmentVariable - Gets the value of an environment variable.
 * @shellInfo: Pointer to the shell info struct.
 * @variableName: The name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *customGetEnvironmentVariable(shellInfo_t *shellInfo, const char *variableName)
{
	list_t *node = shellInfo->environmentList;
	char *position;

	while (node)
	{
		position = customStartsWith(node->str, variableName);
		if (position && *position)
			return (position);
		node = node->next;
	}
	return (NULL);
}

/**
 * customSetEnvironmentVariable - Initializes a new environment variable or modifies an existing one.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customSetEnvironmentVariable(shellInfo_t *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		customEputs("Incorrect number of arguments\n");
		return (1);
	}
	if (customSetEnv(shellInfo, shellInfo->args[1], shellInfo->args[2]))
		return (0);
	return (1);
}

/**
 * customUnsetEnvironmentVariable - Removes an environment variable.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customUnsetEnvironmentVariable(shellInfo_t *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		customEputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		customUnsetEnv(shellInfo, shellInfo->args[i]);

	return (0);
}

/**
 * populateEnvironmentList - Populates the environment linked list.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int populateEnvironmentList(shellInfo_t *shellInfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; shellInfo->environ[i]; i++)
		addNodeEnd(&node, shellInfo->environ[i], 0);
	shellInfo->environmentList = node;
	return (0);
}
