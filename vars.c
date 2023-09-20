#include "shell.h"

/**
 * is_chain - test characters in buffer
 * @info: param structure
 * @buf: character buf
 * @p: address of current position in buf
 *
 * Return: return 1 for chain deli
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t asp = *p;

	if (buf[asp] == '|' && buf[asp + 1] == '|')
	{
		buf[asp] = 0;
		asp++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[asp] == '&' && buf[asp + 1] == '&')
	{
		buf[asp] = 0;
		asp++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[asp] == ';')
	{
		buf[asp] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = asp;
	return (1);
}

/**
 * check_chain - checking stat
 * @info: pm stru
 * @buf: character buff
 * @p: add to position
 * @i: location
 * @len: length for the buffer
 *
 * Return: none
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t asp = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			asp = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			asp = len;
		}
	}

	*p = asp;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
