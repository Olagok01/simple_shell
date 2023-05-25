#include "shell.h"

char *error_126_msg(char **args);
char *error_127_msg(char **args);

/**
 * error_126_msg - function that creates an error message
 *	for permission denied failures.
 * @args: array of arguments passed to the command.
 * Return: error string.
 */
char *error_126_msg(char **args)
{
	int hist = 0;
	char *name = NULL;
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (NULL);
	}
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}


/**
 * error_127_msg - function that creates an error
 *	message for command not found failures.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_127_msg(char **args)
{
	int hist = 0;
	char *name = NULL;
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
	{
		return (NULL);
	}
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
