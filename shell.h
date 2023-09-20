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
 * struct liststr - singl-link list
 * @num: numbering field
 * @str: string
 * @next: to be assigned as next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - includes pseudo-arguement that needs to be passed to our function,
 * alloww uniform prototype to the function pointer-struct
 * @arg: string which is generated from getline containing arguements
 * @argv: array of strings produced from arg
 * @path: string path to current command
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
 * @status: return status of last exec'd command
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

    char **cmd_buf;   /* pointer of the command ; chain_buffer,and memory allocation */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT                                                               \
    {                                                                           \
        NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
            0, 0, 0                                                             \
    }

/**
 * struct builtin - has those builtin string along with related function
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

int _myhelp(info_t *);

/* toem_built1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);

/* toem_getinfo.c */
void set_info(info_t *, char **);
void clear_info(info_t *);

void free_info(info_t *, int);

/* toem_environ.c */

int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
char *_getenv(info_t *, const char *);
int _myunsetenv(info_t *);

/* toem_history.c */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

int renumber_history(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);

/* toem_getenv.c */
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);

int _setenv(info_t *, char *, char *);

/* toem_vars.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

int replace_string(char **, char *);

/* toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* toem_lists1.c */
char **list_to_strings(list_t *);
size_t list_len(const list_t *);

size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);

ssize_t get_node_index(list_t *, list_t *);

/* toem_lists.c */

size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
void free_list(list_t **);

#endif
