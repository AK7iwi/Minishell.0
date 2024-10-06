/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:49 by diguler           #+#    #+#             */
/*   Updated: 2024/10/06 16:15:16 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env(t_env *env)
{
	t_env *current;

	//if (!env)
		//create small env
	current = env;
	while (current)
	{
		printf("%s\n", current->str);
		current = current->next;
	}

	return (EXIT_SUCCESS);
}
