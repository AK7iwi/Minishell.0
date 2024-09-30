
#include "minishell.h"

inline void 	free_error(t_error *error)
{
	error->error_g = 0;
}

static void	ft_putstr(char *str, int fd)
{
	if (fd < 0)
		return ;
	while (*str)
		write(fd, str++, 1);
}

void	msg_error(t_error error)
{
	if (error.error_g & ERROR_MALLOC)
		ft_putstr(E_MALLOC, 2);
	if (error.error_g & ERROR_ARG)
		ft_putstr(E_ARGS, 2);
	if (error.error_g & ERROR_QUOTE)
		ft_putstr(E_QUOTE, 2);
	if (error.error_g & ERROR_OPERATOR)
		ft_putstr(E_OPERATOR, 2);
	if (error.error_g & ERROR_REDIR)
		ft_putstr(E_REDIR, 2);
	if (error.error_g & ERROR_PARAN)
		ft_putstr(E_PARAN, 2);
}