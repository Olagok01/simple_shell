#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **prev_args);
int shell_setenv(char **args, char __attribute__((__unused__)) **prev_args);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **prev_args);


/**
 * shell_env - function that prints the current environment
 * @args: An array of arguments passed to the shell
 * @prev_args: A double pointer to the beginning of args
 * Return: If an error occurs - -1
 *	Otherwise - 0
 * Description: Prints one variable per line in the
 *	format 'variable'='value'.
 */
int shell_env(char **args, char __attribute__((__unused__)) **prev_args)
{
	char **environ_var = NULL;
	int i;
	char nc = '\n';

	if (!environ_var)
	{
		return (-1);
	}
	for (i = 0; environ_var[i]; i++)
	{
		write(STDOUT_FILENO, environ_var[i], _strlen(environ_var[i]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}


/**
 * shell_setenv - function that changes or adds an
 *	environmental variable to the PATH
 * @args: array of arguments
 * @prev_args: double pointer to the beginning of args
 * Description: args[1] is the name of the new or existing PATH variable
 *	args[2] is the value to set the new or changed variable to
 * Return: If an error occurs - -1
 *	Otherwise - 0
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **prev_args)
{
	char **environ_var = NULL;
	char **env_var = NULL, **new_env, *new_val;
	size_t size;
	int index;

	if (!args[0] || !args[1])
	{
		return (create_error_msg(args, -1));
	}
	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
	{
		return (create_error_msg(args, -1));
	}
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ_var[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_val);
		return (create_error_msg(args, -1));
	}

	for (index = 0; environ_var[index]; index++)
	{
		new_env[index] = environ_var[index];
	}
	free(environ_var);
	environ_var = new_env;
	environ_var[index] = new_val;
	environ_var[index + 1] = NULL;

	return (0);
}


/**
 * shell_unsetenv - function that deletes an environmental
 *	variable from the PATH
 * @args: array of arguments
 * @prev_args: double pointer to the beginning of args
 * Description: args[1] is the PATH variable to remove
 * Return: If an error occurs - -1
 *	Otherwise - 0
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **prev_args)
{
	char **environ_var = NULL;
	char **env_var, **new_env;
	size_t size;
	int index, index2;

	if (!args[0])
	{
		return (create_error_msg(args, -1));
	}
	env_var = _getenv(args[0]);
	if (!env_var)
	{
		return (0);
	}
	for (size = 0; environ_var[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
	{
		return (create_error_msg(args, -1));
	}
	for (index = 0, index2 = 0; environ_var[index]; index++)
	{
		if (*env_var == environ_var[index])
		{
			free(*env_var);
			continue;
		}
		new_env[index2] = environ_var[index];
		index2++;
	}
	free(environ_var);
	environ_var = new_env;
	environ_var[size - 1] = NULL;

	return (0);
}
