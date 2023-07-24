#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

/* BUFFERS */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* FOR COMMAND CHAINS */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number function */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* used for getline function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - for singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - it conatins some pseudo arguments to pass
 * a function uniform protoype for a function pointer struct
 * @arg: str generated from getline containing args
 * @av: an arr of strs generated from arg
 * @path: path for the current command
 * @ac: the arg count
 * @line_count: counts errors
 * @err_num: error code for exi fncs
 * @linecount_flag: flags line of input
 * @fname: the prg filename
 * @env: local copy of environ
 * @environ: modified copy of environ from LL env
 * @his: the history node
 * @alias: the alias node
 * @envi_chngd: On if environ was changed
 * @status: the return status of the last exec cmd
 * @cmd_buf: addree of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: reads file descriptor
 * @histcount: the his line number count
 */
typedef struct passinfo
{
	char *arg;
	char **av;
	char *path;
	int ac;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *his;
	list_t *alias;
	char **environ;
	int envi_chngd;
	int status;

	char **cmd_buf; /* ptr to cmd; chain buff, for mem mngmt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin str & related function
 * @type: the builtin cmd flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtint;


/* for shell loop */
int shell_loop(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void for_cmd(info_t *info);

/* for parse.c */
int exec_cmd(info_t *info, char *path);
char *duplicate_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* for loop.c */
int loophsh(char **);

/* for errors function */
void _nputs(char *s);
int _cputchar(char c);
int put_fd(char c, int fd);
int _printfd(char *s, int fd);

/* stringfn.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* stringfn1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
void _puts(char *s);
int _putchar(char c);

/* exitfns.c */
char *_strncpy(char *des, char *source, int n);
char *_strncat(char *des, char *source, int n);
char *our_strchr(char *str, char c);

/* tokens.c */
char **strtow(char *str, char *del);
char **strtow2(char *s, char delim);

/* realloc.c */
char *our_memset(char *s, char b, unsigned int n);
void free_str(char **ss);
void *our_realloc(void *ptr, unsigned int old, unsigned int newsize);

/* mem.c */
int be_fee(void **ptr);

/* atoi.c */
int interactive(info_t *info);
int delimeter(char c, char *delim);
int is_alpha(int c);
int is_atoi(char *str);

/* moerrors.c */
int our_erratoi(char *str);
void print_errs(info_t *info, char *serr);
int prints_dec(int input, int fd);
char *convert_num(long int num, int base, int flags);
void rm_comments(char *buf);

/* builtincmd.c */
int our_hist(info_t *info);
int sets_alias(info_t *info, char s);
int our_alias(info_t *info, char *s);
int prints_alias(list_t *node);
int mim_alias(info_t *info);

/* builtin.c */
int our_exit(info_t *info);
int our_cd(info_t *info);
int _ourhelp(info_t *info);

/* getline.c */
ssize_t input_buffer(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
int get_getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* getinfo */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* envie.c */
int our_env(info_t *info);
char *our_getenv(info_t *info, const char *name);
int our_setenv(info_t *info);
int unset_env(info_t *info);
int pop_env_list(info_t *info);

/* getenvie.c */
char **_getenvie(info_t *info);
int our_unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* hist.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* lists.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *s, int num);
size_t print_list(const list_t *h);
int delete_node(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* morelists.c */
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t printlist(const list_t *h);
list_t *node_start(list_t *node, char *prefix, char c);
ssize_t get_node(list_t *head, list_t *node);

/* varies.c */
int is_chain(info_t *info, char *buff, size_t *ptr);
void check_chain(info_t *info, char *buf, size_t *ptr, size_t j, size_t len);
int replaces_alias(info_t *info);
int replaces_vars(info_t *info);
int replae_string(char **old, char *new);

#endif
