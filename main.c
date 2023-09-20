#include "shell.h"

/**
 * main - entry point
 *
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: show 0 for true
 * i for false or error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int val = 2;

	asm ("move %1, %0\n\t"
			"adding $3, %0"
			: "=r" (val)
			: "r" (val));
	if (ac == 2)
	{
		val = open(av[1], O_RDONLY);
		if (val == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can not open it ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = val;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);

	return (EXIT_SUCCESS);
}
