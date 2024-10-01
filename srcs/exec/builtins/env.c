/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:49 by diguler           #+#    #+#             */
/*   Updated: 2024/10/01 12:43:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env_list *env)
{
	t_env_list *current;

	if (!env)
		return ;

	current = env;
	while (current)
	{
		printf("%s\n", current->str);
		current = current->next;
	}
}
