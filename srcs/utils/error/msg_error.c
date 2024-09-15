
#include "minishell.h"

static void	ft_putstr(char *str, int fd)
{
	if (fd < 0)
		return ;
	while (*str)
		write(fd, str++, 1);
}

void	msg_error(t_error error)
{
	if (error.error_g & ERROR_ARG)
		ft_putstr(E_PARS_ARGS, 2);
}