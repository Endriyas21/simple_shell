# my_shell

## Overview

`my_shell` is a simple Unix shell implementation written in C. It provides basic functionalities of a shell, including command execution, environment variable management, and support for built-in commands. This project aims to mimic the behavior of a Unix shell, allowing users to interact with the system through a command-line interface.

## Features

- **Command Execution**: Execute commands found in the system's PATH.
- **Built-in Commands**:
  - `cd`: Change the current directory.
  - `exit`: Exit the shell.
  - `env`: Print the current environment.
  - `setenv`: Set an environment variable.
  - `unsetenv`: Unset an environment variable.
  - `alias`: Create and display aliases.
  - `history`: Display the command history.
- **Comments Handling**: Ignore comments in command input.
- **Interactive and Non-Interactive Modes**: Support for both interactive and non-interactive usage.
- **Error Handling**: Display appropriate error messages for invalid commands or arguments.
- **Environment Management**: Manage environment variables within the shell.
- **Command History**: Maintain a history of executed commands.

## Installation

To compile the shell, use the following command:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o my_shell
```

Ensure you have `gcc` installed on your system. This command will compile all the C source files in the directory and create an executable named `my_shell`.

## Usage

To start the shell, run the compiled executable:

```sh
./my_shell
```

You can then enter commands as you would in a regular shell. For example:

```sh
$ ls -l
$ cd /path/to/directory
$ echo "Hello, World!"
```

### Interactive Mode

In interactive mode, the shell provides a prompt and waits for user input:

```sh
$ ./my_shell
my_shell> ls
my_shell> cd /path/to/directory
my_shell> exit
```

### Non-Interactive Mode

In non-interactive mode, you can pass a script file to the shell:

```sh
$ echo "ls -l" > script.sh
$ ./my_shell script.sh
```

## Built-in Commands

### `cd`

Change the current directory.

```sh
cd [directory]
```

### `exit`

Exit the shell.

```sh
exit [status]
```

### `env`

Print the current environment.

```sh
env
```

### `setenv`

Set an environment variable.

```sh
setenv VARIABLE VALUE
```

### `unsetenv`

Unset an environment variable.

```sh
unsetenv VARIABLE
```

### `alias`

Create and display aliases.

```sh
alias [name='value']
```

### `history`

Display the command history.

```sh
history
```

## Error Handling

The shell provides error messages for various invalid operations, such as:

- Command not found
- Invalid arguments for built-in commands
- Permission denied

## License

This project is licensed under the MIT License.

We welcome contributions from the community. If you would like to contribute, please fork the repository and submit a pull request.
