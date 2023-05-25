#include "shell.h"

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc -  a function reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @prev_size: size in bytes of the allocated space for ptr
 * @new_size: size in bytes for the new memory block
 * Return: If new_size == prev_size - ptr
 *	If new_size == 0 and ptr is not NULL - NULL
 *	Otherwise - a pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	void *memory;
	char *src, *dest;
	unsigned int index;

	if (new_size == prev_size)
	{
		return (ptr);
	}
	if (ptr == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
		{
			return (NULL);
		}
		return (memory);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	src = ptr;
	memory = malloc(sizeof(*src) * new_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}
	dest = memory;

	for (index = 0; index < prev_size && index < new_size; index++)
	{
		dest[index] = *src++;
	}
	free(ptr);
	return (memory);
}


/**
 * assign_lineptr - a function that reassigns the lineptr variable for _getline
 * @lineptr: buffer to store an input string
 * @n: The size of lineptr
 * @buffer: The string to assign to lineptr
 * @buf: The size of buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t buf)
{
	if (*lineptr == NULL)
	{
		if (buf > 120)
		{
			*n = buf;
		}
		else
		{
			*n = 120;
		}
		*lineptr = buffer;
	}
	else if (*n < buf)
	{
		if (buf > 120)
		{
			*n = buf;
		}
		else
		{
			*n = 120;
		}
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}


/**
 * _getline - function that reads input_size from a stream
 * @lineptr: buf to store the input_size
 * @n: size of lineptr
 * @stream: stream to be read from
 * Return: number of bytes to be read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input_size = 0;
	ssize_t result;
	char c = 'x', *buf;
	int read_f;

	if (input_size == 0)
	{
		fflush(stream);
	}
	else
	{
		return (-1);
	}
	input_size = 0;

	buf = malloc(sizeof(char) * 120);
	if (!buf)
	{
		return (-1);
	}
	while (c != '\n')
	{
		read_f = read(STDIN_FILENO, &c, 1);
		if (read_f == -1 || (read_f == 0 && input_size == 0))
		{
			free(buf);
			return (-1);
		}
		if (read_f == 0 && input_size != 0)
		{
			input_size++;
			break;
		}
		if (input_size >= 120)
		{
			buf = _realloc(buf, input_size, input_size + 1);
		}
		buf[input_size] = c;
		input_size++;
	}
	buf[input_size] = '\0';

	assign_lineptr(lineptr, n, buf, input_size);

	result = input_size;
	if (read_f != 0)
	{
		input_size = 0;
	}
	return (result);
}
