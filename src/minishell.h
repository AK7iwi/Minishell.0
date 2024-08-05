#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../libft/libft.h"

#define ERR_MALLOC "malloc error\n"
#define ERR_PIPE "pipe error\n"
#define ERR_FORK "fork error\n"

#define EXT_MALLOC 1
#define EXT_PIPE 1
#define EXT_FORK 1

extern pid_t g_signal_pid;

typedef struct s_cmd
{
    bool skip_cmd;
    int infile;
    int outfile;
    char **cmd_param;
    struct s_cmd *prev;
    struct s_cmd *next;
} t_cmd;

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_env_list
{
    char *str;
    struct s_env_list *prev;
    struct s_env_list *next;
} t_env_list;

typedef struct s_data
{
    t_env_list *env;
    t_token *token;
    t_cmd *cmd;
    int exit_code;
    int pip[2];
    bool sq;
} t_data;

void quoting_choice(bool *dquote, bool *squote, int *i, char c);
int open_quote(t_data *data, char *line);
char *get_env_value(char *var, t_env_list *env);
char *extract_var_name(char *str, int *i);
char *replace_env_vars(char *line, t_env_list *env);
void replace_dollars_in_command(char **line, t_env_list *env);
t_env_list *create_env_list(char **envp);
void free_env_list(t_env_list **lst);
void append_env_list(t_env_list **lst, char *str);

#endif
