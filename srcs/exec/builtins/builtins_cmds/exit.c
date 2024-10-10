/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:29:48 by diguler           #+#    #+#             */
/*   Updated: 2024/10/10 17:07:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_exit(char **args)
{
	uint8_t exit_status;
	
	exit_status = 0;
	
	printf("exit\n");
	if (args[2])
	{
		exit_status = 1;
		printf("bash: exit: too many arguments\n");
	}
	else if (args[1])
	{
		if (!is_number(args[1]))
		{
			exit_status = 2;	
			printf("bash: exit: %s: numeric argument required\n", args[1]);
		}
		else 
			exit_status = ft_atoi(args[1]);
	}
	
	exit(exit_status);
}