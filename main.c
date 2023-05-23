#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

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
 * main - Function that uns a simple UNIX command interpreter
 * @argc: number of arguments
 * @argv: array of pointers to the arguments.
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int result = 0, ret_end;
	int *exit_ret = &ret_end;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
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
		while (result != END_OF_FILE && ret != EXIT)
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
