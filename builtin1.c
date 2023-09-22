#include "shell.h"

/**
 * customHistory - Displays the command history list.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customHistory(shellInfo_t *shellInfo)
{
	printCommandList(shellInfo->commandHistory);
	return (0);
}

/**
 * customUnsetAlias - Unsets an alias.
 * @shellInfo: Pointer to the shell info struct.
 * @aliasString: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int customUnsetAlias(shellInfo_t *shellInfo, char *aliasString)
{
	char *equalSignPosition, character;
	int result;
        equalSignPosition = customStrFindChar(aliasString, '=');
	if (!equalSignPosition)
		return (1);
	character = *equalSignPosition;
	*equalSignPosition = 0;
	result = deleteNodeAtIndex(&(shellInfo->aliasList),
		getNodeIndex(shellInfo->aliasList, nodeStartsWith(shellInfo->aliasList, aliasString, -1)));
	*equalSignPosition = character;
	return (result);
}

/**
 * customSetAlias - Sets an alias.
 * @shellInfo: Pointer to the shell info struct.
 * @aliasString: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int customSetAlias(shellInfo_t *shellInfo, char *aliasString)
{
	char *equalSignPosition;
        equalSignPosition = customStrFindChar(aliasString, '=');
	if (!equalSignPosition)
		return (1);
	if (!*++equalSignPosition)
		return (customUnsetAlias(shellInfo, aliasString));

	customUnsetAlias(shellInfo, aliasString);
	addNodeEnd(&(shellInfo->aliasList), aliasString, 0);
	return 0;
}

/**
 * customPrintAlias - Prints an alias string.
 * @node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error.
 */
int customPrintAlias(list_t *node)
{
	char *position = NULL, *alias = NULL;

	if (node)
	{
		position = customStrchr(node->str, '=');
		for (alias = node->str; alias <= position; alias++)
			customPutchar(*alias);
		customPutchar('\'');
		customPuts(position + 1);
		customPuts("'\n");
		return (0);
	}
	return (1);
}

/**
 * customAlias - Mimics the alias builtin (man alias).
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customAlias(shellInfo_t *shellInfo)
{
	int index = 0;
	char *position = NULL;
	list_t *node = NULL;

	if (shellInfo->argc == 1)
	{
		node = shellInfo->aliasList;
		while (node)
		{
			customPrintAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; shellInfo->args[index]; index++)
	{
		position = customStrchr(shellInfo->args[index], '=');
		if (position)
			customSetAlias(shellInfo, shellInfo->args[index]);
		else
			customPrintAlias(nodeStartsWith(shellInfo->aliasList, shellInfo->args[index], '='));
	}

	return (0);
}
