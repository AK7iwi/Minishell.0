#ifndef MINISHELL_H
# define MINISHELL_H

//**********************************************//
//					INCLUDES					//
//**********************************************//

#include "errors.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>

//**********************************************//
//					DEFINES						//
//**********************************************//

/* Special characters */

#define SPACE 						' '
#define NULL_CHAR					'\0'
#define S_QUOTE						'\''
#define D_QUOTE						'\"'
#define ENV_VAR						'$'

//**********************************************//
//					ENUM						//
//**********************************************//

typedef enum e_tok_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SIMPLE_REDIRECT_IN,
	TOKEN_SIMPLE_REDIRECT_OUT,
	TOKEN_HERE_DOC,
	TOKEN_DOUBLE_REDIRECT_OUT,
	TOKEN_ENV_VAR,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
}	t_tok_type;

typedef enum e_ast_type
{
    AST_COMMAND,
    AST_OPERATOR,
	AST_SUBSH,
}	t_ast_type;

typedef enum e_op_type
{
    AST_PIPE,
	AST_AND,
	AST_OR,
}	t_op_type;

//**********************************************//
//					STRUCTURES					//
//**********************************************//

typedef struct s_env_list
{
    char *str;

    struct s_env_list *prev;
    struct s_env_list *next;
}	t_env_list;

typedef struct s_cmd
{
	//t_cmd_type
	char **args;
}	t_cmd;

typedef struct s_operator
{
	t_op_type	type;

    struct s_ast *left;
    struct s_ast *right;  
} 	t_operator;

typedef struct s_subshell
{
    struct s_ast *root;
} 	t_subshell;

typedef struct s_ast
{
    t_ast_type  type;

    union
    {
        t_cmd      cmd;
        t_operator operator;
        t_subshell subshell;
    };
} 	t_ast;

typedef struct s_token
{
    t_tok_type type;
    char	*str;
    
    struct s_token *prev;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
	t_error 	error;
    t_token		*token;
	t_ast 		*ast;
    t_env_list	*env;
} 	t_data;


//**********************************************//
//					EXEC	   					//
//**********************************************//

//**********************************************//
//					ENV     	   				//
//**********************************************//

/* env_initializer.c */
void 	print_env(t_env_list *env);
void 	free_env(t_env_list **lst);
bool 	add_to_env_list(t_env_list **lst, char *str);
bool	init_env(t_data *data, char **envp);

//**********************************************//
//					BUILTINS	   				//
//**********************************************//

/* exit.c */
void	ft_exit(t_data *data, char **command);
/* env.c */
int		env(t_env_list *env);
/* unset.c */
void	unset(char **args, t_env_list **env);
/* export.c */
int		ft_export(char **args, t_env_list *env);
/* pwd.c */
void	pwd(void);
/* cd.c */
int 	cd(char **args, t_env_list *env);
/* echo.c */
void	echo(char **args);
/* builtins.c */
bool	is_builtins(t_data *data);

/* exec.c */
bool 	ast_exec(t_ast *root);
bool	exec(t_data *data, char **envp);

//**********************************************//
//					PARSER   					//
//**********************************************//

//**********************************************//
//					PARSER_UTILS   				//
//**********************************************//

/* parse_checker2.c */
bool	is_or(t_tok_type type);
bool	is_and(t_tok_type type);
bool	is_pipe(t_tok_type type);
bool 	is_open_paren(t_tok_type type);
bool 	is_closed_paren(t_tok_type type);

/* parse_checker.c */
bool 	is_cmd(t_tok_type type);
bool	is_redir(t_tok_type type);
bool	is_operator(t_tok_type type);

//**********************************************//
//					AST   						//
//**********************************************//

/* ast_print.c */
void 	print_ast(t_ast *ast, int depth);

/* ast_free.c */
void	ast_freer(t_ast **ast);

/* operator_node.c */
t_ast	*operator_node_creator(t_ast *left, t_ast *right, t_op_type op_type);

/* cmd_node.c */
t_ast	*node_cmd_creator(t_ast **new_node, t_token **current);

/*subsh_node.c */
t_ast	*subsh_node_creator(t_ast **new_node, t_token **current);

/* ast.c */
t_ast	*ast_cmd_and_subsh_handler(t_token **current);
void	ast_op_handler(t_ast ** result, t_token **current, uint8_t min_prec);
t_ast	*ast_algo(t_token **current, uint8_t min_prec);
bool	ast_creator(t_data *data);

//**********************************************//
//					SYNER   					//
//**********************************************//

/* syn_checker.c */
bool	paren_checker(t_token *current, uint32_t *o_counter, uint32_t *c_counter);
bool 	redir_checker(t_token *current);
bool 	operator_checker(t_token *current);

/* syn_analyzer.c */
bool	syn_analyzer(t_data *data);

//**********************************************//
//					LEXER    					//
//**********************************************//

/* token_utils.c */
void 		print_token_list(t_token *head);
void		free_token(t_token **tokens);
bool		add_token(t_token **token_struct, t_tok_type *token, char *str_token);
t_tok_type	wich_token(char *str);

//////////// Handle special character ///////////////////

/* special_char_len.c */
uint8_t get_special_char_len(char *input, size_t *i);

/* special_char_extracter.c*/
char*	special_char_extracter(t_error *error, char *input, size_t *i);

/* special_char_handler.c */
bool	is_special_char(char *input, size_t *i);
bool 	special_char_handler(t_data *data, char *input, t_tok_type *token, size_t *index);

//////////// Handle str ///////////////////

/* str_len.c */
bool	get_quotes_len(char *input, ssize_t *str_len, t_tok_type *t, size_t *i);
ssize_t	get_str_len(char *input, t_tok_type *token, size_t *i);

/* str_extracter.c */
char*	str_extracter(t_error *error, char *input, t_tok_type *token, size_t *index);

/* str_handler.c */
bool 	str_handler(t_data *data, char *input, t_tok_type *token, size_t *index);

/* tokenizer.c */
bool	tokenizer(t_data *data, char *input);

//**********************************************//
//					UTILS   					//
//**********************************************//

/* free.c */
void	free_loop(t_data *data);
// void	free_all(t_data *data);

//////////////// Libft ////////////////

/* lib_checker.c */
int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/* lib_memory.c */
char	*ft_strdup(const char *s);
/* lib_len.c */
size_t	ft_strlen(const char *s);

#endif /* MINISHELL_H */