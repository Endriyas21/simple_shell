#include "shell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    shellInfo_t shellInfo;
    shellInfo.argc = ac;
    shellInfo.args = av;

    // Initialize other relevant variables here

    if (ac == 2)
    {
        // Handle file redirection if needed
    }

    // Populate the environment list
    populateEnvironmentList(&shellInfo);

    // Read command history
    // readHistoryFromFile(&shellInfo);

    // Start the shell loop
    runShell(&shellInfo, av);

    return 0;
}
