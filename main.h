#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* buffer size for read and write */
#define BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* command chaining options */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for number conversion */
#define CONVERT_HEX		1
#define CONVERT_UNSIGNED	2

/* for custom getline function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

extern char **environ;

/**
 * struct list_s - singly linked list
 * @num: number field
 * @str: string
 * @next: pointer to next node
 */
typedef struct list_s
{
	int num;
	char *str;
	struct list_s *next;
} list_t;

/**
 *struct _passinfo - contains pseudo-arguements to pass into a function.
 *@arg: a string generated from getline containing arguements
 *@argv: string array of CL argumnets
 *@path: path for the current command
 *@argc: number of CL arguments
 *@line_count: error count
 *@err_num: error code for exit function
 *@linecount_flag: count this line of input when on
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from local env
 *@history: command history
 *@alias: for alias
 *@env_changed: checks if environ was changed
 *@status: return status of last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd for reading command line input
 *@histcount: history line number count
 */
typedef struct _passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; /* for memory mangement */
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct _builtin - contains builtin string and function ptr
 *@type: builtin command flag
 *@func: function pointer
 */
typedef struct _builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;

/* hsh functions */
int loop_hsh(info_t *, char **);
int search_builtin(info_t *);
void _trace_cmd(info_t *);
void _forkcmd(info_t *);

/* path functions*/
int _iscmd(info_t *, char *);
char *_chars_dup(char *, int, int);
char *_path_trace(info_t *, char *, char *);

/* error functions */
void err_puts(char *);
void err_print(info_t *, char *);
int err_putc(char);
int fd_putc(char, int);
int fd_puts(char *, int);

/* string functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strstart(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strstr(char *, char *);
char *_strchr(char *, char);

/* memory functions */
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_buff(void **);

/* helper functions */
void _puts(char *);
int _putchar(char);
int _isdelim(char, char *);
int _isalpha(int);
void handle_comments(char *);

/* conversion functions */
int dec_print(int, int);
int _atoi(char *);
char *_convert_num(long int, int, int);
int err_atoi(char *);
char **strtow(char *, char *);

/* builtin emulators */
int _hshexit(info_t *);
int _hshcd(info_t *);
int _hshhelp(info_t *);
int _hshhistory(info_t *);
int _hshalias(info_t *);

/* module for alias */
int _alias_unset(info_t *, char *);
int _alias_set(info_t *, char *);
int _alias_print(list_t *);

/* module for getline */
ssize_t _getinput(info_t *);
int get_line(info_t *, char **, size_t *);
void _sigint_handle(int);
ssize_t _buff_input(info_t *, char **, size_t *);
ssize_t _buff_read(info_t *, char *, size_t *);

/* module for info */
void _info_unset(info_t *);
void _info_set(info_t *, char **);
void _info_free(info_t *, int);
int mode_interact(info_t *);

/*module for env */
char *get_env(info_t *, const char *);
int _hshenv(info_t *);
int _hshsetenv(info_t *);
int _hshunsetenv(info_t *);
int fill_env_list(info_t *);
char **_get_hshenv(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* module for chain */
int _ischain(info_t *, char *, size_t *);
void _chain_check(info_t *, char *, size_t *, size_t, size_t);
int _alias_tr(info_t *);
int _var_tr(info_t *);
int _str_tr(char **, char *);

/* file input/output_functions */
char *hist_get(info_t *);
int hist_write(info_t *);
int hist_read(info_t *);
int hist_build(info_t *, char *, int);
int hist_renum(info_t *);

/* lists_t functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_liststr(const list_t *);
int delete_node_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **str_from_list(list_t *);
size_t print_list(const list_t *);
list_t *node_strstart(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif /* #ifndef _MAIN_H_ */

