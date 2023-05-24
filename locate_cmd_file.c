#include "shell.h"

char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);


/**
 * get_location - locates a command in the PATH
 * @command: command to locate
 * Return: If an error occurs or the command cannot be located - NULL.
 *	Otherwise - the full pathname of the command.
 */
char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *first;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
	{
		return (NULL);
	}
	dirs = get_path_dir(*path + 5);
	first = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
		{
			return (NULL);
		}
		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list_link(first);
			return (temp);
		}

		dirs = dirs->next_node;
		free(temp);
	}

	free_list_link(first);

	return (NULL);
}


/**
 * fill_path_dir - Copies path but also replaces sandwiched/trailing
 *	colons (:) with current working directory
 * @path: the colon-separated list of directories
 * Return: copy of path with any sandwiched/trailing colons replaced
 *	with the current working directory
 */
char *fill_path_dir(char *path)
{
	int index, len = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (index = 0; path[index]; index++)
	{
		if (path[index] == ':')
		{
			if (path[index + 1] == ':' || index == 0 || path[index + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
	{
		return (NULL);
	}
	path_copy[0] = '\0';
	for (index = 0; path[index]; index++)
	{
		if (path[index] == ':')
		{
			if (index == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[index + 1] == ':' || path[index + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[index], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - tokenizes a colon-separated list of
 *	directories into a list_s linked list
 * @path: colon-separated list of directories
 * Return: pointer to the initialized linked list
 */
list_t *get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *first = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
	{
		return (NULL);
	}
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
	{
		return (NULL);
	}
	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&first, dirs[index]) == NULL)
		{
			free_list_link(first);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (first);
}
