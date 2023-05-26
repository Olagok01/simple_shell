#include "shell.h"

void free_args(char **args, char **prev_args);
char *get_process_id(void);
char *get_env_value(char *env_var, int len);
void variable_replace(char **args, int *exit_ret);

/**
 * free_args - function that frees up memory taken by args
 * @args: A null-terminated double pointer containing arguments
 * @prev_args: A double pointer to the beginning of args
 */
void free_args(char **args, char **prev_args)
{
	size_t index;

	for (index = 0; args[index] || args[index + 1]; index++)
	{
		free(args[index]);
	}
	free(prev_args);
}


/**
 * get_process_id - function that gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *	information about the current process. The PID is the
 *	first word in the file. The function reads the PID into
 *	a buffer and replace the space at the end with a \0 byte.
 * Return: current process ID or NULL on failure.
 */
char *get_process_id(void)
{
	size_t index = 0;
	char *pid_buffer;
	ssize_t file_des;

	file_des = open("/proc/self/stat", O_RDONLY);
	if (file_des == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	pid_buffer = malloc(120);
	if (!pid_buffer)
	{
		close(file_des);
		return (NULL);
	}
	read(file_des, pid_buffer, 120);
	while (pid_buffer[index] != ' ')
	{
		index++;
	}
	pid_buffer[index] = '\0';
	close(file_des);
	return (pid_buffer);
}



/**
 * get_env_value - function that gets the value corresponding
 *	to an environmental variable.
 * @env_var: the environmental variable to search for
 * @len: length of the environmental variable to search for
 * Return: If the variable is not found - an empty string
 *	Otherwise - the value of the environmental variable
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *env_var, int len)
{
	char **var_address;
	char *result = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
	{
		return (NULL);
	}
	var[0] = '\0';
	_strncat(var, env_var, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		temp = *var_address;
		while (*temp != '=')
		{
			temp++;
		}
		temp++;
		result = malloc(_strlen(temp) + 1);
		if (result)
		{
			_strcpy(result, temp);
		}
	}

	return (result);
}


/**
 * variable_replace - function that handles variable replacement
 * @line: A double pointer containing the command and arguments
 * @exit_ret: A pointer to the return value of the last executed command
 * Description: Replaces $$ with the current PID, $? with the return value
 *	of the last executed program, and envrionmental variables
 *	preceded by $ with their corresponding value.
 */
void variable_replace(char **line, int *exit_ret)
{
	int j, k = 0, length;
	char *result = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				result = get_process_id();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				result = _itoa(*exit_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				length = k - (j + 1);
				result = get_env_value(&old_line[j + 1], length);
			}
			new_line = malloc(j + _strlen(result)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
			{
				return;
			}
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (result)
			{
				_strcat(new_line, result);
				free(result);
				result = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
