#ifndef SHELL_H
#define SHELL_H

/*
 * File: shell.h
 * Authors: Oluwatobiloba Light
 *          Princewill Chimdi Samuel
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define SHELLY_END_OF_FILE -2
#define SHELLY_EXIT -3

/* Global environemnt */
extern char **environ;
char *name;
int history;

/**
 * struct sh_builtin - struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @func: A function pointer to the builtin command's function.
 */
typedef struct sh_builtin
{
	char *name;
	int (*func)(char **argv, char **head);
} sh_builtin_t;

/**
 * struct sh_singly_list - struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct sh_singly_list.
 */
typedef struct sh_singly_list
{
	char *dir;
	struct sh_singly_list *next;
} sh_singly_list_t;

/**
 * struct sh_alias - struct defining aliases.
 * @name: The name of the alias.
 * @val: The value of the alias.
 * @next: A pointer to another struct sh_alias.
 */
typedef struct sh_alias
{
	char *name;
	char *val;
	struct sh_alias *next;
} sh_alias_t;

/* Global aliases linked list */
sh_alias_t *aliases;

/* STRING HELPER FUNCTIONS */
char *shelly_strcat(char *, const char *);
char *shelly_strncat(char *, const char *, size_t);
char *shelly_strchr(char *, char);
char *shelly_strcpy(char *, const char *);
int shelly_strcmp(char *, char *);
int shelly_strncmp(const char *, const char *, size_t);
int shelly_strspn(char *, char *);
int shelly_strlen(const char *);

/* MAIN HELPER FUNCTIONS */
ssize_t shelly_getline(char **, size_t *, FILE *);
int shelly_execute(char **, char **);
char *shelly_itoa(int);
sh_singly_list_t *shelly_get_path_dir(char *);
void *shelly_realloc(void *, unsigned int, unsigned int);
void shelly_free_list(sh_singly_list_t *);
char *shelly_get_loc(char *);
char **shelly_strtok(char *, char *);

int shelly_proc_commands(char *, int *);

/* INPUT HANDLERS */
int shelly_handle_args(int *);
char *shelly_get_args(char *, int *);
void shelly_handle_line(char **, ssize_t);
void shelly_replace_variable(char **, int *);
int shelly_run_args(char **, char **, int *);
int shelly_call_args(char **, char **, int *);
int shelly_check_args(char **);
void shelly_free_args(char **, char **);
char **shelly_replace_aliases(char **);
ssize_t shelly_get_new_len(char *);

/* BUILTIN FUNCTIONS*/
int shelly_exit(char **, char **);
int shelly_env(char **, char __attribute__((__unused__)) **);
int shelly_setenv(char **, char __attribute__((__unused__)) **);
int (*shelly_get_builtin(char *))(char **, char **);
int shelly_unsetenv(char **, char __attribute__((__unused__)) **);
int shelly_cd(char **, char __attribute__((__unused__)) **);
int shelly_alias(char **, char __attribute__((__unused__)) **);
int shelly_help(char **, char __attribute__((__unused__)) **);
int shelly_cd_helper(char **, char *, struct stat);
int shelly_cd_helper2(char *, char *, char **);

/* ERROR HANDLER FUNCTIONS */
char *shelly_error_2_exit(char **);
char *shelly_error_env(char **);
char *shelly_error_126(char **);
char *shelly_error_1(char **);
char *shelly_error_2_syntax(char **);
int shelly_create_error(char **, int);
char *shelly_error_127(char **);
char *shelly_error_2_cd(char **);

/* HELP HANDLERS */
void shelly_help_setenv(void);
void shelly_help_cd(void);
void shelly_help_exit(void);
void shelly_help_env(void);
void shelly_help_help(void);
void shelly_help_alias(void);
void shelly_help_unsetenv(void);
void shelly_help_all(void);

/* LIST HANDLERS */
sh_alias_t *shelly_add_alias_end(sh_alias_t **, char *, char *);
sh_singly_list_t *shelly_add_node_end(sh_singly_list_t **, char *);
void shelly_free_alias_list(sh_alias_t *);
void shelly_free_list(sh_singly_list_t *);

/* BUILTIN HELPER FUNCTIONS */
char **shelly_copyenv(void);
void shelly_free_env(void);
char **shelly_getenv(const char *);

#endif /* SHELL_H */
