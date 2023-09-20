#include "shell.h"

/**
 * input_buf - for buff. commands
 * @info: pm
 * @buf: buf name
 * @len: name for len
 *
 * Return: show
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t mt = 0;
	size_t meter = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		mt = getline(buf, &meter, stdin);
#else
		mt = _getline(info, buf, &meter);
#endif
		if (mt > 0)
		{
			if ((*buf)[mt - 1] == '\n')
			{
				(*buf)[mt - 1] = '\0';
				mt--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = mt;
			info->cmd_buf = buf;
		}
	}
	return (mt);
}

/**
 * get_input - new linw
 * @info: pm
 *
 * Return: revel
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t yt, zt, len;
	ssize_t mt = 0;
	char **buf_p = &(info->arg), *ter;

	_putchar(BUF_FLUSH);
	mt = input_buf(info, &buf, &len);
	if (mt == -1)
		return (-1);
	if (len)
	{
		zt = yt;
		ter = buf + yt;

		check_chain(info, buf, &zt, yt, len);
		while (zt < len)
		{
			if (is_chain(info, buf, &zt))
				break;
			zt++;
		}

		yt = zt + 1;
		if (yt >= len)
		{
			yt = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ter;
		return (_strlen(ter));
	}

	*buf_p = buf;
	return (mt);
}

/**
 * read_buf - analyze buf
 * @info: pm
 * @buf: buf
 * @yt: how big
 *
 * Return: mt
 */
ssize_t read_buf(info_t *info, char *buf, size_t *yt)
{
	ssize_t mt = 0;

	if (*yt)
		return (0);
	mt = read(info->readfd, buf, READ_BUF_SIZE);
	if (mt >= 0)
		*yt = mt;
	return (mt);
}

/**
 * _getline - next liner
 * @info: pm
 * @ptr: add
 * @length: big
 *
 * Return: show
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t yt, len;
	size_t k;
	ssize_t mt = 0, wh = 0;
	char *ter = NULL, *point = NULL, *ano;

	ter = *ptr;
	if (ter && length)
		wh = *length;
	if (yt == len)
		yt = len = 0;

	mt = read_buf(info, buf, &len);
	if (mt == -1 || (mt == 0 && len == 0))
		return (-1);

	ano = _strchr(buf + yt, '\n');
	k = ano ? 1 + (unsigned int)(ano - buf) : len;
	point = _realloc(ter, wh, wh ? wh + k : k + 1);
	if (!point) /* MALLOC FAILURE! */
		return (ter ? free(ter), -1 : -1);

	if (wh)
		_strncat(point, buf + yt, k - yt);
	else
		_strncpy(point, buf + yt, k - yt + 1);

	wh += k - yt;
	yt = k;
	ter = point;

	if (length)
		*length = wh;
	*ptr = ter;
	return (wh);
}

/**
 * sigintHandler - prevent cont
 * @sig_num: show the num
 *
 * Return: none
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
