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

void variable_replacement(char **args, int *exit_ret);

/** input.c */
char *get_args(char *line, int *exit_ret);
int call_args(char **args, char **prev_args, int *exit_ret);
int run_args(char **args, char **prev_args, int *exit_ret);
int handle_args(int *exit_ret);
int check_args(char **args);

/** lnked list */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list_link(list_t *head);

/** error_message.c */
int num_length(int num);
char *_itoa(int num);
int create_error_msg(char **args, int err);

/** environ_var.c */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);


void sig_handler(int sig);

/** helper_1.c and helper_2.c */
void free_args(char **args, char **prev_args);
char *get_process_id(void);
char *get_env_value(char *env_var, int len);
void variable_replace(char **args, int *exit_ret);
void modify_line(char **line, ssize_t read);
ssize_t calculate_new_len(char *line);
void log_operators(char *line, ssize_t *new_length);


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
