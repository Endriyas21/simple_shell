#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>

#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

/* reading and writing of buffers */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
/* lines of command chain */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
/* converting_numbers() */
#define CONVERT_UNSIGNED 2
#define CONVERT_LOWERCASE 1

/* one if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
extern char **environ;

/**
 * struct liststr - single-link list
 * @num: numbering field
 * @str: string
 * @next: to be assigned as the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * struct passinfo - includes pseudo-argument that needs to be passed to our
 * function, allows uniform prototype to the function pointer-struct
 * @arg: string which is generated from getline containing arguments
 * @argv: array of strings produced from arg
 * @path: string path to the current command
 * @argc: argument-count
 * @line_count: error-count
 * @err_num: error code to the exit()s
 * @linecount_flag: on count this line of input
 * @fname: the program filename
 * @env: linked-list copy of environ
 * @environ: modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ got changes
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer for the cmd_buf, on if chaining
 * @cmd_buf_type: Command_type ||, &&, ;
 * @readfd: this is fd from where to read line input
 * @histcount: the history line num_count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf;
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{ \
NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0 \
}

/**
 * struct builtin - has hose builtin string along with the related function
 * @type: indicates the builtin command_flag
 * @func: refers to the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);

/* toem_string.c */
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strlen(char *);

/* toem_errors.c */
int _eputchar(char);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
void _eputs(char *);

/* toem_string_one.c */
void _puts(char *);

char *_strdup(const char *);
char *_strcpy(char *, char *);
int _putchar(char);
/* toem_tokenize.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_reallocing.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);

void *_realloc(void *, unsigned int, unsigned int);

/* loophshing.c */
int loophsh(char **);
/* toem_memory.c */
int bfree(void **);

/* toem_exit.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);

/* toem_strint.c */
int interactive(info_t *);
int _strint(char *);
int _isalpha(int);
int is_dt(char, char *);

/* toem_errors1.c */
void print_error(info_t *, char *);
int print_d(int, int);
int _erratoi(char *);
void remove_comments(char *);
char *convert_number(long int, int, int);

/* toem_built.c */
int _mydir(info_t *);
int _exiter(info_t *);

#endif
