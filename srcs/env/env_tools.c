/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:40:13 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/06 18:00:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env **env_var)
{
    t_env	*tmp;

    while (*env_var)
    {
        tmp = (*env_var)->next;
        free((*env_var)->str);
        free(*env_var);
        *env_var = tmp;
    }
}
bool set_env_var(t_env *current, char* env_var, char *new_value)
{
	free(current->str);
	current->str = ft_strjoin(env_var, new_value);
	return (current->str);
}
bool add_env_var(t_env **env_var, char *str)
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
	
    if (*env_var == NULL) 
    {
        new_node->prev = NULL;
        *env_var = new_node;
        return (EXIT_SUCCESS);
    }
	last = *env_var;
    while (last->next)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;

	return (EXIT_SUCCESS);
}