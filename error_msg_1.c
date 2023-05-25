#include "shell.h"


char *error_env_msg(char **args);
char *error_1_msg(char **args);
char *error_exit_msg(char **args);
char *error_cd_msg(char **args);
char *error_syntax_msg(char **args);

/**
 * error_env_msg - Creates an error message for shellby_env errors.
 * @args: array of arguments passed to the command
 * Return: error string
 */
char *error_env_msg(char **args)
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

	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1_msg - function that creates error message for shellby_alias errors
 * @args: array of arguments passed to the command
 * Return: error string.
 */
char *error_1_msg(char **args)
{
	char *name = NULL;
	char *error;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		return (NULL);
	}
	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_exit_msg - function that creates an
 *	error message for shellby_exit errors
 * @args: array of arguments passed to the command
 * Return: error string
 */
char *error_exit_msg(char **args)
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
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_cd_msg - function that creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_cd_msg(char **args)
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
	if (args[0][0] == '-')
	{
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
	{
		_strcat(error, ": cd: Illegal option ");
	}
	else
	{
		_strcat(error, ": cd: can't cd to ");
	}
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_syntax_msg - fucntion that creates an error message for syntax errors
 * @args: array of arguments passed to the command
 * Return: error string
 */
char *error_syntax_msg(char **args)
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
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
