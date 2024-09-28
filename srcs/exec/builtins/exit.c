/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:29:48 by diguler           #+#    #+#             */
/*   Updated: 2024/09/28 12:49:32 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	nb;

	i = 0;
	n = 1;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = -n;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * n);
}

int	ft_isdigit(int c)
{
	if (c >= 0 && c <= 9)
		return (c);
	return (0);
}

void	handle_num_error(char **command)
{
	printf("bash: exit: ");
	printf("%s", command[1]);
	printf(": numeric argument required\n");
	// g_sig.status = 1;
}

int	count_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_invalid_num(char *command)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (command[i])
	{
		if ((command[i] == '-' || command[i] == '+') && sign > 0)
			return (1);
		else if ((command[0] == '-' || command[0] == '+') && command[0 + 1])
			sign++;
		else if (!ft_isdigit(command[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_exit_code(char *command)
{
	int	exit;

	exit = 0;
	exit = ft_atoi(command);
	if (is_invalid_num(command) && exit == 0)
		exit = 2;
	else if (exit > 255)
		exit = exit % 256;
	else if (exit < 0)
		exit = 256 + (exit % 256);
	return (exit);
}

void	ft_exit(t_data *data, char **command)
{
	int i;

	(void)data;
	i = count_args(command);

	if (i > 2 && !is_invalid_num(command[1]) && command[2])
	{
		printf("bash: exit: too many arguments\n");
		return;
	}
	else if (i > 1 && is_invalid_num(command[1]))
	{
		handle_num_error(command);
		return;
	}
	if (command[1])
	{
		int exit_code = parse_exit_code(command[1]);
		printf("exit\n");
		exit(exit_code);
	}
	printf("exit\n");
	exit(0);
}

