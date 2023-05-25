#include "shell.h"

void sig_handler(int sig);
int execute_cmd(char **args, char **prev_args);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}


/**
 * execute_cmd - function that executes a command in a child process
 * @args: array of arguments
 * @prev_args: double pointer to the beginning of args
 * Return: If an error occurs - a corresponding error code
 *	O/w - The exit value of the last executed command
 */
int execute_cmd(char **args, char **prev_args)
{
	char **environ_var = NULL;
	alias_t *aliases = NULL;
	pid_t child_pid;
	int status, flag = 0, result = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
		{
			result = (create_error_msg(args, 126));
		}
		else
		{
			result = (create_error_msg(args, 127));
		}
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
			{
				free(command);
			}
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ_var);
			if (errno == EACCES)
			{
				result = (create_error_msg(args, 126));
			}
			free_env();
			free_args(args, prev_args);
			free_alias_list(aliases);
			_exit(result);
		}
		else
		{
			wait(&status);
			result = WEXITSTATUS(status);
		}
	}
	if (flag)
	{
		free(command);
	}
	return (result);
}


/**
 * main - Function that uns a simple UNIX command interpreter
 * @argc: number of arguments
 * @argv: array of pointers to the arguments.
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	extern char **environ;
	alias_t *aliases;
	int result = 0, ret_end;
	int *exit_ret = &ret_end;
	char **environ_var = environ;
	char *prompt = "$ ", *new_line = "\n";
	
	/**name = argv[0]; */
	/**hist = 1;*/
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exit_ret = 0;
	environ_var = _copyenv();
	if (!environ_var)
	{
		exit(-100);
	}
	if (argc != 1)
	{
		result = process_file(argv[1], exit_ret);
		free_env();
		free_alias_list(aliases);
		return (*exit_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (result != END_OF_FILE && result != EXIT)
		{
			result = handle_args(exit_ret);
		}
		free_env();
		free_alias_list(aliases);
		return (*exit_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		result = handle_args(exit_ret);
		if (result == END_OF_FILE || result == EXIT)
		{
			if (result == END_OF_FILE)
			{
				write(STDOUT_FILENO, new_line, 1);
			}
			free_env();
			free_alias_list(aliases);
			exit(*exit_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exit_ret);
}
