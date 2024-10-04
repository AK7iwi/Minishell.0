/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initializerc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:16:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/04 09:30:09 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env_list **lst)
{
    t_env_list *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->str);
        free(*lst);
        *lst = tmp;
    }
}
bool add_to_env_list(t_env_list **lst, char *str)
{
    t_env_list *new_node;
    t_env_list *last;
	
	new_node = malloc(sizeof(t_env_list));
    if (!new_node)
        return (EXIT_FAILURE);
	
    new_node->str = ft_strdup(str); // protect
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
bool	init_env(t_data *data, char **envp)
{
    size_t i;

	i = 0;
    while (envp[i]) 
    {
		if (add_to_env_list(&data->env, envp[i]))
			return (EXIT_FAILURE); ///error malloc
        i++;
    }

	return (EXIT_SUCCESS);
}