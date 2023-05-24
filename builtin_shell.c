#include "shell.h"


int (*get_builtin(char *command))(char **args, char **prev_args);
int shell_exit(char **args, char **prev_args);
int shell_cd(char **args, char __attribute__((__unused__)) **prev_args);



/**
 * get_builtin - Matches a command with a corresponding
 *	shellby builtin function.
 * @command: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **prev_args)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}


/**
 * shell_exit - function that causes normal process termination for the shell.
 * @args: An array of arguments containing the exit value.
 * @prev_args: A double pointer to the beginning of args.
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shell_exit(char **args, char **prev_args)
{
	int index, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			index = 1;
			len_of_int++;
		}
		for (; args[0][index]; index++)
		{
			if (index <= len_of_int && args[0][index] >= '0' && args[0][index] <= '9')
				num = (num * 10) + (args[0][index] - '0');
			else
				return (create_error_msg(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
	{
		return (create_error_msg(--args, 2));
	}
	args -= 1;
	free_args(args, prev_args);
	free_env();
	free_alias_list(aliases);
	exit(num);
}


/**
 * shell_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @prev_args: A double pointer to the beginning of args.
 * Return: If the given string is not a directory - 2.
 *	If an error occurs - -1.
 *	Otherwise - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **prev_args)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
	{
		return (-1);
	}
	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error_msg(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error_msg(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

