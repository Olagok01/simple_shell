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

void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


/** environ.c */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);


void sig_handler(int sig);

/** str_function_1 .c */
int _strlen(const char *s);
char *_strncat(char *dest, const char *src, int n);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

#endif
