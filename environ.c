#include "shell.h"

/**
 * _myenv - prints current env
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - to get value of environ variable
 * @info: Struct with potential arguments
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *z;

	while (node)
	{
		z = starts_with(node->str, name);
		if (z && *z)
			return (z);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Init new env var,
 *             otherwise to modify existing var
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("wrong num of arguement\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an env var
 *
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * populate_env_list - populate linked list
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);
	info->env = node;
	return (0);
}
