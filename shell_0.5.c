#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

extern char **environ; // Declare the environment variable

int main(void)
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE / 2]; // Assuming each argument is a single word

    while (1)
    {
        printf(":) "); /* Display the prompt */
        fflush(stdout); /* Flush the output buffer to ensure the prompt is displayed */

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }

        /* Check if the input is not empty */
        if (strlen(input) > 0)
        {
            /* Tokenize the input into arguments */
            int num_args = 0;
            char *token = strtok(input, " ");
            while (token != NULL)
            {
                args[num_args++] = token;
                token = strtok(NULL, " ");
            }
            args[num_args] = NULL; // Null-terminate the argument list

            /* Check if the command is the env built-in */
            if (strcmp(args[0], "env") == 0)
            {
                char **env = environ;
                while (*env != NULL)
                {
                    printf("%s\n", *env);
                    env++;
                }
            }
            else
            {
                /* Check if the command exists in the PATH */
                char *command = args[0];
                char *path = getenv("PATH");
                char *path_copy = strdup(path);
                char *dir = strtok(path_copy, ":");

                int found = 0;
                while (dir != NULL)
                {
                    char full_path[MAX_INPUT_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

                    if (access(full_path, X_OK) == 0)
                    {
                        found = 1;
                        break;
                    }

                    dir = strtok(NULL, ":");
                }

                free(path_copy);

                if (found)
                {
                    /* Use the fork and execve functions to execute the command */
                    pid_t pid = fork();

                    if (pid == -1)
                    {
                        perror("fork");
                    }
                    else if (pid == 0)
                    {
                        /* Child process */
                        if (execve(args[0], args, NULL) == -1)
                        {
                            /* Handle execution error */
                            perror(args[0]);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        /* Parent process */
                        int status;
                        if (waitpid(pid, &status, 0) == -1)
                        {
                            perror("waitpid");
                        }
                    }
                }
                else
                {
                    printf("%s: command not found\n", command);
                }
            }
        }
    }

    return (0);
}
