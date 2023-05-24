#include "shell.h"

void modify_line(char **line, ssize_t read);
ssize_t calculate_new_len(char *line);
void log_operators(char *line, ssize_t *new_length);

/**
 * modify_line - partitions a line read from standard input as needed
 * @line: A pointer to a line read from standard input
 * @read: The length of line
 * Description: Spaces are inserted to separate ";", "||", and "&&"
 *	Replaces "#" with '\0'
 */
void modify_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, cur, next;
	size_t i, j;
	ssize_t new_length;

	new_length = calculate_new_len(*line);
	if (new_length == read - 1)
	{
		return;
	}
	new_line = malloc(new_length + 1);
	if (!new_line)
	{
		return;
	}
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		cur = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (cur == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && previous != ' ')
				{
					new_line[j++] = ' ';
				}
				else if (previous == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && previous != ' ')
				{
					new_line[j++]  = ' ';
				}
				else if (previous == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * calculate_new_len - function that gets the new length of a line partitioned
 *	by ";", "||", "&&&", or "#"
 * @line: The line to check
 * Return: The new length of the line
 * Description: Cuts short lines containing '#' comments with '\0'
 */

ssize_t calculate_new_len(char *line)
{
	size_t index;
	ssize_t new_length = 0;
	char cur, next;

	for (index = 0; line[index]; index++)
	{
		cur = line[index];
		next = line[index + 1];
		if (cur == '#')
		{
			if (index == 0 || line[index - 1] == ' ')
			{
				line[index] = '\0';
				break;
			}
		}
		else if (index != 0)
		{
			if (cur == ';')
			{
				if (next == ';' && line[index - 1] != ' ' && line[index - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[index - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[index - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				log_operators(&line[index], &new_length);
		}
		else if (cur == ';')
		{
			if (index != 0 && line[index - 1] != ' ')
			{
				new_length++;
			}
			if (next != ' ' && next != ';')
			{
				new_length++;
			}
		}
		new_length++;
	}
	return (new_length);
}


/**
 * log_operators - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_length: Pointer to new_len in get_new_len function.
 */
void log_operators(char *line, ssize_t *new_length)
{
	char prev, cur, next;

	prev = *(line - 1);
	cur = *line;
	next = *(line + 1);

	if (cur == '&')
	{
		if (next == '&' && prev != ' ')
		{
			(*new_length)++;
		}
		else if (prev == '&' && next != ' ')
		{
			(*new_length)++;
		}
	}
	else if (cur == '|')
	{
		if (next == '|' && prev != ' ')
		{
			(*new_length)++;
		}
		else if (prev == '|' && next != ' ')
		{
			(*new_length)++;
		}
	}
}
