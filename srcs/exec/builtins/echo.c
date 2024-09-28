/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:53:11 by diguler           #+#    #+#             */
/*   Updated: 2024/09/28 12:17:12 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int is_flag_n(const char *arg)
// {
// 	int i;

// 	i = 2;
	
// 	if(arg[0] != '=' || arg[1] != 'n')
// 		return (0);
	
// 	while(arg[i])
// 	{
// 		if(arg[i] != 'n')
// 			return (0);
// 		i++; 
// 	}
// 	return(1);
// }

static int	check_flags(char **args)
{
	int	i;
	
	i = 1;
	
	while (args[i] && ft_strncmp(args[i], "-n", 2)== 0 
		&& ft_strlen(args[i]) == 2)
		i++;
	
	return (i);
}

void	echo(char **args)
{
	int newline;
	int i;

	i = check_flags(args);
	newline = (i == 1);

	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if(args[i])
			printf(" ");
	}
	
	if (newline)
		printf("\n");
}