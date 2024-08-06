#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define WORD		6	

typedef struct s_token
{
    char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}   t_token;

empereur'du'caca < sasukaka;
str = empereur'du'caca;
type = mot;

str = <;
type = oper;

str = sasukaka;
type = mot; 

#endif
