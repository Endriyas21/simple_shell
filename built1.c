#include "shell.h"

/**
 * _myhistory - to show hist list, preceded
 *  by line num, beginig from 0.
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *a, d;
    int ret;

    a = _strchr(str, '=');
    if (!a)
        return (1);
    d = *a;
    *a = 0;
    ret = delete_node_at_index(&(info->alias),
                               get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *a = d;
    return (ret);
}

/**
 * set_alias - change alias to str
 * @info: pm struct
 * @str: str alias
 *
 * Return:  0 for success and i to errors
 */
int set_alias(info_t *info, char *str)
{
    char *a;

    a = _strchr(str, '=');
    if (!a)
        return (1);
    if (!*++a)
        return (unset_alias(info, str));

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - alias str
 * @node: alias node
 *
 * Return: 0 for success and i to errors
 */
int print_alias(list_t *node)
{
    char *a = NULL, *a = NULL;

    if (node)
    {
        a = _strchr(node->str, '=');
        for (a = node->str; a <= a; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(a + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias -alias built
 * @info: Struct with potential arguments
 *  const fun proto.
 *  Return: 0
 */
int _myalias(info_t *info)
{
    int i = 0;
    char *a = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        a = _strchr(info->argv[i], '=');
        if (a)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
