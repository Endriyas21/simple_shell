#include "shell.h"

/**
 * customExit - Exit the shell.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Exits with a given exit status.
 * (0) if shellInfo->args[0] != "exit".
 */
int customExit(shellInfo_t *shellInfo)
{
	int exitStatus = 0;

	if (shellInfo->args[1]) /* If there is an exit argument */
	{
		exitStatus = customAtoi(shellInfo->args[1]);
		if (exitStatus == -1)
		{
			shellInfo->statusCode = 2;
			printError(shellInfo, "Illegal number: ");
			printErrorMessage(shellInfo->args[1]);
			printNewLine();
			return (1);
		}
	        shellInfo->errorCode = exitStatus; 
	}
	else{
		shellInfo->errorCode = 0;
	}
      return exitStatus;
}

/**
 * customChangeDirectory - Change the current directory of the process.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customChangeDirectory(shellInfo_t *shellInfo)
{
	char *currentDirectory, *targetDirectory, buffer[1024];
	int changeDirectoryResult;

	currentDirectory = getcwd(buffer, 1024);
	if (!currentDirectory)
		printMessage("TODO: >>getcwd failure message here<<\n");
	if (!shellInfo->args[1])
	{
		targetDirectory = customGetEnv(shellInfo, "HOME=");
		if (!targetDirectory)
			changeDirectoryResult = /* TODO: What should this be? */
				changeDirectory((targetDirectory = customGetEnv(shellInfo, "PWD=")) ? targetDirectory : "/");
		else
			changeDirectoryResult = changeDirectory(targetDirectory);
	}
	else if (customStringCompare(shellInfo->args[1], "-") == 0)
	{
		if (!customGetEnv(shellInfo, "OLDPWD="))
		{
			printMessage(currentDirectory);
			printNewLine();
			return (1);
		}
		printMessage(customGetEnv(shellInfo, "OLDPWD="));
		printNewLine();
		changeDirectoryResult = /* TODO: What should this be? */
			changeDirectory((targetDirectory = customGetEnv(shellInfo, "OLDPWD=")) ? targetDirectory : "/");
	}
	else
		changeDirectoryResult = changeDirectory(shellInfo->args[1]);
	if (changeDirectoryResult == -1)
	{
		printError(shellInfo, "can't cd to ");
		printErrorMessage(shellInfo->args[1]);
		printNewLine();
	}
	else
	{
		customSetEnv(shellInfo, "OLDPWD", customGetEnv(shellInfo, "PWD="));
		customSetEnv(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * customHelp - Display a help message.
 * @shellInfo: Pointer to the shell info struct.
 *
 * Return: Always 0.
 */
int customHelp(shellInfo_t *shellInfo)
{
	char **argumentArray;

	argumentArray = shellInfo->args;
	printMessage("Help call works. Function not yet implemented.\n");
	if (0)
		printMessage(*argumentArray); /* Temporary attribute unused workaround */
	return (0);
}
