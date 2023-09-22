#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for buffer sizes */
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define CONVERT_UNSIGNED 0x1
#define CONVERT_LOWERCASE 0x2


/* Data structures */
typedef struct list {
    char *str;
    struct list *next;
} list_t;

typedef struct shellInfo {
    char **environ;
    list_t *environmentList;
    list_t *aliasList;
    list_t *commandHistory;
    int argc;
    char **args;
    char *fname;
    int lineCount;
    char **argv;
    int readDescriptor;
} shellInfo_t;

typedef struct info {
    const char *fname;
    int lineCount;
    char **argv;
} info_t;

/* Function prototypes */
void printStringList(char **list);
char *customStartsWith(const char *str, const char *prefix);
void customEputs(const char *string);
int customSetEnv(shellInfo_t *shellInfo, const char *name, const char *value);
int customUnsetEnv(shellInfo_t *shellInfo, const char *name);
void addNodeEnd(list_t **head, const char *str, int num);

int customEnv(shellInfo_t *shellInfo);
char *customGetEnvironmentVariable(shellInfo_t *shellInfo, const char *variableName);
int customSetEnvironmentVariable(shellInfo_t *shellInfo);
int customUnsetEnvironmentVariable(shellInfo_t *shellInfo);
int populateEnvironmentList(shellInfo_t *shellInfo);

int customEputchar(char character);
int customPutFileDescriptor(char character, int fd);
int customPutsFileDescriptor(char *string, int fd);

int customErrAtoi(char *str);
void customPrintErrorMsg(shellInfo_t *info, char *errMsg);
int customPrintDecimal(int num, int fd);
char *customConvertNumber(long int num, int base, int flags);
void customRemoveComments(char *buffer);

char *customStrCopy(char *destination, char *source, int numChars);
char *customStrConcat(char *destination, char *source, int numBytes);
char *customStrFindChar(char *string, char character);

char **splitString(char *str, char *delimiter);
char **splitStringWithChar(char *str, char delimiter);

int runShell(shellInfo_t *shellInfo, char **av);
int findAndExecuteBuiltin(shellInfo_t *shellInfo);
void findAndExecuteCommand(shellInfo_t *shellInfo);
void forkAndExecuteCommand(shellInfo_t *shellInfo);

void printCommandList(list_t *list);
int deleteNodeAtIndex(list_t **head, int index);
int getNodeIndex(list_t *head, int index);
list_t *nodeStartsWith(list_t *head, char *str, char endChar);
char *customStrFindChar(char *str, char target);
void customPutchar(char c);
void customPuts(char *str);

#endif
