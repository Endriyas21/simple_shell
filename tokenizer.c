#include "shell.h"

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: string
 * @d: delimiter str
 *
 * Return: ptr
 */
char **strtow(char *str, char *d)
{
	int new, fr, st, vr, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (new = 0; str[new] != '\0'; new++)
		if (!is_delim(str[new], d) && (is_delim(str[new + 1], d) || !str[new + 1]))
			num++;

	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (new = 0, fr = 0; fr < num; fr++)
	{
		while (is_delim(str[new], d))
			new++;
		st = 0;
		while (!is_delim(str[new + st], d) && str[new + st])
			st++;
		s[fr] = malloc((st + 1) * sizeof(char));
		if (!s[fr])
		{
			for (st = 0; st < fr; st++)
				free(s[st]);
			free(s);
			return (NULL);
		}
		for (vr = 0; vr < st; vr++)
			s[fr][vr] = str[new++];
		s[fr][vr] = 0;
	}
	s[fr] = NULL;
	return (s);
}

/**
 * strtow2 - split
 * @str: input str
 * @d: delimiter
 *
 * Return: ptr to an arr
 */
char **strtow2(char *str, char d)
{
	int new, fr, st, vr, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (new = 0; str[new] != '\0'; new++)
		if ((str[new] != d && str[new + 1] == d) ||
		    (str[new] != d && !str[new + 1]) || str[new + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (new = 0, fr = 0; fr < num; fr++)
	{
		while (str[new] == d && str[new] != d)
			new++;
		st = 0;
		while (str[new + st] != d && str[new + st] && str[new + st] != d)
			st++;
		s[fr] = malloc((st + 1) * sizeof(char));
		if (!s[fr])
		{
			for (st = 0; st < fr; st++)
				free(s[st]);
			free(s);
			return (NULL);
		}
		for (vr = 0; vr < st; vr++)
			s[fr][vr] = str[new++];
		s[fr][vr] = 0;
	}
	s[fr] = NULL;
	return (s);
}
