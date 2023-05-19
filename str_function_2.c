#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * char *_strchr - function that locates a character in a string.
 * @s: string to be searched
 * @c: character to find
 * Return: pointer to that character found in the string
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
	{
		return (&s[i]);
	}
	else
	{
		return (NULL);
	}
}

/**
 * _strspn - function that gets the length of a prefix substring.
 * @s: string to be searched for
 * @accept: prefix to be measured
 * Return: length of bytes in for the prefix substring
 */
int _strspn(char *s, char *accept)
{
	int i;
	int j;
	int length = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				length++;
				break;
			}
			if (accept[j + 1] == '\0')
			{
				return (length);
			}
		}

	}
	return (length);
}

/**
 * _strcmp - Compares pointers to two strings.
 * @s1: A pointer to the first string to be compared.
 * @s2: A pointer to the second string to be compared.
 * Return: If str1 < str2, the negative difference of the
 *	first unmatched characters.
 *         If str1 == str2, 0.
 *         If str1 > str2, the positive difference of the
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
	{
		return (*s1 - *s2);
	}
	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 * Return: Less than 0 if s1 is shorter than s2.
 *	0 if s1 and s2 match.
 *	Greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
		{
			return (s1[i] - s2[i]);
		}
		else if (s1[i] < s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	if (i == n)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}
