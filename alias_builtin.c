#include "shell.h"

int shell_alias(char **args, char __attribute__((__unused__)) **prev_args);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
char **replace_aliases(char **args);

/**
 * shell_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: array of arguments.
 * @prev_args: double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *	Otherwise - 0.
 */
int shell_alias(char **args, char __attribute__((__unused__)) **prev_args)
{
	alias_t *aliases = NULL;
	alias_t *temp = aliases;
	int index, result = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next_node;
		}
		return (result);
	}
	for (index = 0; args[index]; index++)
	{
		temp = aliases;
		value = _strchr(args[index], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[index], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next_node;
			}
			if (!temp)
				result = create_error_msg(args + index, 1);
		}
		else
		{
			set_alias(args[index], value);
		}
	}
	return (result);
}


/**
 * set_alias - function that will either set an existing
 *	alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'
 * @var_name: the name of the alias
 * @value: Value of the alias. First character is a '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *aliases = NULL;
	alias_t *temp = aliases;
	int length, j, k;
	char *new_val;

	*value = '\0';
	value++;
	length = _strlen(value) - _strspn(value, "'\"");
	new_val = malloc(sizeof(char) * (length + 1));
	if (!new_val)
	{
		return;
	}
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_val[k++] = value[j];
	}
	new_val[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_val;
			break;
		}
		temp = temp->next_node;
	}
	if (!temp)
	{
		add_alias_end(&aliases, var_name, new_val);
	}
}


/**
 * print_alias - function that prints the alias in the format name='value'
 * @alias: Pointer to an alias
 */
void print_alias(alias_t *alias)
{
	char *alias_str;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_str = malloc(sizeof(char) * (length + 1));
	if (!alias_str)
	{
		return;
	}
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, length);
	free(alias_str);
}


/**
 * replace_aliases - goes through the arguments and replace any matching alias
 * with their value
 * @args: 2D pointer to the arguments
 * Return: 2D pointer to the arguments
 */
char **replace_aliases(char **args)
{
	alias_t *aliases = NULL;
	alias_t *temp;
	int index;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
	{
		return (args);
	}
	for (index = 0; args[index]; index++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[index], temp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, temp->value);
				free(args[index]);
				args[index] = new_val;
				index--;
				break;
			}
			temp = temp->next_node;
		}
	}
	return (args);
}
