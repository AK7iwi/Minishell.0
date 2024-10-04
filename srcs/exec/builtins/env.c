/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:49:49 by diguler           #+#    #+#             */
/*   Updated: 2024/10/04 09:33:17 by diguler          ###   ########.fr       */
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