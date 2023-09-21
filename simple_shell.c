#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        printf("#cisfun$ "); /* Display the prompt */
        fflush(stdout);     /* Flush the output buffer to ensure the prompt is displayed */

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
            /* Use the fork and execve functions to execute the command */
            pid_t pid = fork();

            if (pid == -1)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                /* Child process */
                if (execve(input, NULL, NULL) == -1)
                {
                    /* Handle execution error */
                    perror(input);
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
    }

    return (0);
}
