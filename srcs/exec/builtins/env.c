/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:49 by diguler           #+#    #+#             */
/*   Updated: 2024/09/30 12:25:16 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_var(t_env_list *env)
{
	if (env->str && ft_strchr(env->str, '='))
	{
		printf("%s\n", env->str);
		return (1);
	}
	return (0);
}

int handle_empty_env(t_env_list *env)
{
	if (!env)
	{
		printf("No environment variables found.\n");
		return (-1);
	}
	return (0);
}

int handle_no_valid_env(int count)
{
	if (count == 0)
	{
		printf("No valid environment variables found.\n");
		return (-2);
	}
	return (0);
}

bool	env(t_env_list *env)
{
	t_env_list *temp;
	int count;

	if (handle_empty_env(env))
		return (-1);

	count = 0;
	temp = env;
	while (temp)
	{
		if (print_env_var(temp) == 1)
			count++;
		temp = temp->next;
		if (temp == env)
			break;
	}

	return (handle_no_valid_env(count));
}
