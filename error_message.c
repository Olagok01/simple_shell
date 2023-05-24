#include "shell.h"

int num_length(int num);
char *_itoa(int num);
int create_error_msg(char **args, int err);

/**
 * num_len - function that counts the digit length of a number
 * @num: number to measure
 * Return: the digit length
 */
int num_length(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}
	return (length);
}


/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buf;
	int length = num_length(num);
	unsigned int num1;

	buf = malloc(sizeof(char) * (length + 1));
	if (!buf)
	{
		return (NULL);
	}
	buf[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buf[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buf[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buf);
}

/**
 * create_error_msg - function that writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: the error value
 * Return: The error value
 */
int create_error_msg(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env_msg(args);
		break;
	case 1:
		error = error_1_msg(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
		{
			error = error_exit_msg(++args);
		}
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
		{
			error = error_syntax_msg(args);
		}
		else
		{
			error = error_cd_msg(args);
		}
		break;
	case 126:
		error = error_126_msg(args);
		break;
	case 127:
		error = error_127_msg(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
	{
		free(error);
	}
	return (err);

}
