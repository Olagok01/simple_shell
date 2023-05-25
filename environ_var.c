#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - function that creates a copy of the environment.
 * Return: if an error occurs - NULL.
 *	O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **environ_var = NULL;
	char **new_environ;
	size_t size;
	int i;

	for (size = 0; environ_var[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
	{
		return (NULL);
	}
	for (i = 0; environ_var[i]; i++)
	{
		new_environ[i] = malloc(_strlen(new_environ[i]) + 1);
		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
			{
				free(new_environ[i]);
			}
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[i], new_environ[i]);
	}
	new_environ[i] = NULL;
	return (new_environ);
}


/**
 * free_env - Function that frees the the environment copy.
 */
void free_env(void)
{
	char **environ_var = NULL;
	int index;

	for (index = 0; environ_var[index]; index++)
	{
		free(environ_var[index]);
	}
	free(environ_var);
}


/**
 * _getenv - fucntion that gets an environmental variable from the PATH
 * @var: name of the environmental variable to get
 * Return: if the environmental variable does not exist - NULL
 *	Otherwise - a pointer to the environmental variable
 */
char **_getenv(const char *var)
{
	char **environ_var = NULL;
	int i, length;

	length = _strlen(var);
	for (i = 0; environ_var[i]; i++)
	{
		if (_strncmp(var, environ_var[i], length) == 0)
		{
			return (&environ_var[i]);
		}
	}
	return (NULL);
}
