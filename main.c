#include "shell.h"

void sig_handler(int sig);

/**
 * signal_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void signal_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, signal_handler);
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
	int ret = 0, ret_end;
	int *exit_ret = &ret_end;
	char *prompt = "cisfun$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, signal_handler);
	*exit_ret = 0;
	environ_var = _copyenv();
	if (!environ_var)
		exit(-100);
	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exit_ret);
		free_env();
		free_alias_list(aliases);
		return (*exit_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exit_ret);
		free_env();
		free_alias_list(aliases);
		return (*exit_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exit_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exit_ret);
		}
	}
	free_env();
	free_alias_list(aliases);
	return (*exit_ret);
}
