#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3


/* Global environemnt */
extern char **environ_var;
/* Global program name */
char *name;
/* Global history counter */
int hist;


/**
 * struct list_s -  new struct type defining a linked list.
 * @dir: directory path.
 * @next: pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next_node;
} list_t;


/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next_node;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


/** lnked list */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list_link(list_t *head);


/** environ_var.c */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);


void sig_handler(int sig);

/** str_function_1 .c */
int _strlen(const char *s);
char *_strncat(char *dest, const char *src, int n);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);


/** str_fcuntion_2.c */
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, int n);



#endif
