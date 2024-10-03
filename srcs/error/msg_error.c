
#include "minishell.h"

inline void 	free_error(t_error *error)
{
	error->error_gen = 0;
	error->error_parsing = 0;
	error->error_exec = 0;
}

static void	ft_putstr(char *str, int fd)
{
	if (fd < 0)
		return ;
	while (*str)
		write(fd, str++, 1);
}

static void	error_exec_msg(uint16_t error)
{

}
static void	error_parsing_msg(uint8_t error)
{
	if (error.error_parsing & ERROR_ARG)
		ft_putstr(E_ARGS, 2);
	if (error.error_parsing & ERROR_QUOTE)
		ft_putstr(E_QUOTE, 2);
	if (error.error_parsing & ERROR_OPERATOR)
		ft_putstr(E_OPERATOR, 2);
	if (error.error_parsing & ERROR_REDIR)
		ft_putstr(E_REDIR, 2);
	if (error.error_parsing & ERROR_PARAN)
		ft_putstr(E_PARAN, 2);
}
static void 	error_gen_msg(uint8_t error)
{
	if (error.error_gen & ERROR_MALLOC)
		ft_putstr(E_MALLOC, 2);
}

void errors_displayer(t_error error)
{
	if (error.error_gen)
		error_gen_msg(error.error_gen);
	if (error.error_parsing)
		error_parsing_msg(error.error_parsing);
	if (error.error_exec)
		error_exec_msg(error.error_exec);
}