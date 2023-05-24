#include "shell.h"

char *get_args(char *line, int *exit_ret);
int call_args(char **args, char **prev_args, int *exit_ret);
int run_args(char **args, char **prev_args, int *exit_ret);
int handle_args(int *exit_ret);
int check_args(char **args);

/**
 * get_args - function that gets a command from standard input
 * @line: buffer to store the command
 * @exit_ret: return value of the last executed command
 * Return: If an error occurs - NULL.
 *	Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exit_ret)
{
	size_t n = 0;
	ssize_t read_file;
	char *prompt = "$ ";

	if (line)
	{
		free(line);
	}
	read_file = _getline(&line, &n, STDIN_FILENO);

	if (read_file == -1)
	{
		return (NULL);
	}
	if (read_file == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prompt, 2);
		}
		return (get_args(line, exit_ret));
	}

	line[read_file - 1] = '\0';
	variable_replace(&line, exit_ret);
	modify_line(&line, read_file);
	return (line);
}

/**
 * call_args - function to partitions operators from commands and calls them
 * @args: array of arguments
 * @prev_args: double pointer to the beginning of args
 * @exit_ret: value of the parent process last executed command
 * Return: value of the last executed command.
 */
int call_args(char **args, char **prev_args, int *exit_ret)
{
	int result, i;

	if (!args[0])
	{
		return (*exit_ret);
	}
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			result = run_args(args, prev_args, exit_ret);
			if (*exit_ret != 0)
			{
				args = &args[++i];
				index = 0;
			}
			else
			{
				for (index++; args[i]; i++)
				{
					free(args[i]);
				}
				return (result);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			result = run_args(args, prev_args, exit_ret);
			if (*exit_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
				{
					free(args[i]);
				}
				return (result);
			}
		}
	}
	args = replace_aliases(args);
	result = run_args(args, prev_args, exit_ret);
	return (result);
}

/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @prev_args: A double pointer to the beginning of args.
 * @exit_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **prev_args, int *exit_ret)
{
	int result, index;
	int (*builtin)(char **args, char **prev_args);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		result = builtin(args + 1, prev_args);
		if (result != EXIT)
		{
			*exit_ret = result;
		}
	}
	else
	{
		*exit_ret = execute(args, prev_args);
		result = *exit_ret;
	}
	hist++;

	for (index = 0; args[index]; index++)
	{
		free(args[index]);
	}
	return (result);
}

/**
 * handle_args - function that gets, calls, and runs the execution of a command
 * @exit_ret: The return value of the parent process' last executed command
 * Return: If an end-of-file is read - END_OF_FILE (-2)
 *	If the input cannot be tokenized - -1
 *	O/w - The exit value of the last executed command.
 */
int handle_args(int *exit_ret)
{
	int result = 0, index;
	char **args, *line = NULL, **prev_args;

	line = get_args(line, exit_ret);
	if (!line)
	{
		return (END_OF_FILE);
	}
	args = _strtok(line, " ");
	free(line);
	if (!args)
	{
		return (result);
	}
	if (check_args(args) != 0)
	{
		*exit_ret = 2;
		free_args(args, args);
		return (*exit_ret);
	}
	prev_args = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			result = call_args(args, prev_args, exit_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
	{
		result = call_args(args, prev_args, exit_ret);
	}
	free(prev_args);
	return (result);
}

/**
 * check_args - function that checks if there are
 *	any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2
 *	Otherwise - 0
 */
int check_args(char **args)
{
	size_t index;
	char *current, *next;

	for (index = 0; args[index]; index++)
	{
		current = args[index];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (index == 0 || current[1] == ';')
			{
				return (create_error_msg(&args[index], 2));
			}
			next = args[index + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
			{
				return (create_error_msg(&args[index + 1], 2));
			}
		}
	}
	return (0);
}
