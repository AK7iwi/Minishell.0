/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:40:13 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/05 12:59:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env **lst)
{
    t_env *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->str);
        free(*lst);
        *lst = tmp;
    }
}
bool add_env_var(t_env **lst, char *str)
{
    t_env *new_node;
    t_env *last;
	
	new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (EXIT_FAILURE);
	
    new_node->str = ft_strdup(str);
	if (!(new_node->str))
		return (EXIT_FAILURE);
    new_node->next = NULL;
	
    if (*lst == NULL) 
    {
        new_node->prev = NULL;
        *lst = new_node;
        return (EXIT_SUCCESS);
    }
	last = *lst;
    while (last->next)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;

	return (EXIT_SUCCESS);
}