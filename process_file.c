#include "shell.h"

int cant_open_file(char *file_path);
int process_file(char *file_path, int *exit_ret);

/**
 * cant_open_file - if the file doesn't exist or lacks
 *	proper permissions, print a cant open error
 * @file_path: Path to the supposed file
 * Return: 127
 */

int cant_open_file(char *file_path)
{
	int hist = 0;
	char *name = NULL;
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (127);
	}
	length = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * process_file - function that takes a file and attempts
 *	to run the commands stored within.
 * @file_path: Path to the file.
 * @exit_ret: Return value of the last executed command.
 * Return: If file couldn't be opened - 127.
 *	If malloc fails - -1.
 *	Otherwise the return value of the last command ran.
 */
int process_file(char *file_path, int *exit_ret)
{
	ssize_t file, read_file, index;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **prev_args;
	char buffer[120];
	int result;

	/**hist = 0;*/
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exit_ret = cant_open_file(file_path);
		return (*exit_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		read_file = read(file, buffer, 119);
		if (read_file == 0 && line_size == 0)
		{
			return (*exit_ret);
		}
		buffer[read_file] = '\0';
		line_size += read_file;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (read_file);
	for (index = 0; line[index] == '\n'; index++)
		line[index] = ' ';
	for (; index < line_size; index++)
	{
		if (line[index] == '\n')
		{
			line[index] = ';';
			for (index += 1; index < line_size && line[index] == '\n'; index++)
			{
				line[index] = ' ';
			}
		}
	}
	variable_replace(&line, exit_ret);
	modify_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
	{
		return (0);
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

	result = call_args(args, prev_args, exit_ret);
	free(prev_args);
	return (result);
}
