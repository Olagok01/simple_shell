#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - function that locates the delimiter index marking the end
 *	of the first token contained within a string.
 * @str: string to search
 * @delim: delimiter character
 * Return: delimiter index marking the end of
 *	the intitial token pointed to be str
 */
int token_len(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}
	return (length);
}

/**
 * count_tokens - function that counts the number of delimited
 *	words contained within a string
 * @str: The string to search
 * @delim: The delimiter character
 * Return: number of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, length = 0;

	for (index = 0; *(str + index); index++)
	{
		length++;
	}
	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}
	return (tokens);
}


/**
 * _strtok - function that tokenizes a string
 * @line: string
 * @delim: delimiter character to tokenize the string by
 * Return: pointer to an array containing the tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
	{
		return (NULL);
	}
	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
	{
		return (NULL);
	}
	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *delim)
		{
			i++;
		}
		letters = token_len(line + i, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
			{
				free(ptr[i]);
			}
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
