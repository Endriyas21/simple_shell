#include "shell_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Function to retrieve the PATH environment variable */
char *get_path(void) {
    return getenv("PATH");
}

/* Function to check if a command exists in the PATH */
int check_command_exists(const char *command) {
    char *path = get_path();
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");

    int found = 0;
    while (dir != NULL) {
        char full_path[MAX_INPUT_SIZE];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0) {
            found = 1;
            break;
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return found;
}
