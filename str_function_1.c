#include "shell.h"

int _strlen(const char *s);
char *_strncat(char *dest, const char *src, int n);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != '\0'; length++)
	{
	}
	return (length);
}

/**
 * _strncat - Concatenates two strings using at most
 *	an inputted number of bytes from src.
 * @dest: The string to be appended upon.
 * @src: The string to be appended to dest.
 * @n: The number of bytes from src to be appended to dest.
 * Return: A pointer to the resulting string dest.
 */
char *_strncat(char *dest, const char *src, int n)
{
	int i;
	int length = 0;

	for (i = 0; dest[i] != 0; i++)
	{
		length++;
	}
	for (i = 0; i < n && src[i] != 0; i++)
	{
		dest[length++] = src[i];
	}
	dest[length] = '\0';
	return (dest);
}

/**
 * _strcpy - Copies a string pointed to by @src, including the
 *           terminating null byte, to a buffer pointed to by @dest.
 * @dest: A buffer to copy the string to.
 * @src: The source string to copy.
 * Return: A pointer to the destination string @dest.
 */
char *_strcpy(char *dest, const char *src)
{
	int index = 0;

	while (src[index])
	{
		dest[index] = src[index];
		index++;

	}
	dest[index] = '\0';
	return (dest);
}

/**
 * _strcat - Concatenates the string pointed to by @src
 *	including the terminatig
 * @dest: A pointer to the string to be concatenated upon.
 * @src: The source string to be appended to @dest.
 * Return: A pointer to the destination string @dest.
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int length = 0;

	for (i = 0; dest[i] != '\0'; i++)
	{
		length++;
	}
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[length++] = src[i];
	}
	dest[length] = '\0';
	return (dest);
}
