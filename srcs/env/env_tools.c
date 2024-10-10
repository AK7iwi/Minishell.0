/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:40:13 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/10 12:40:38 by mfeldman         ###   ########.fr       */
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
void	unset_env_var(t_env **env, char *var)
{
    t_env *current;

	current = *env;
    while (current)
    {
        if (ft_strncmp(current->str, var, ft_strlen(var)) == 0 
			&& (current->str[ft_strlen(var)] == '='
			|| current->str[ft_strlen(var)] == '\0'))
            return (remove_env_node(env, current));
        current = current->next;
    }
}
bool set_env_var(t_env **env, char *var_name, char *new_env_var)
{
	t_env *current;

	current = *env;
	//get_my_env
	while (current)
	{
		if (ft_strncmp(current->str, var_name, ft_strlen(var_name)) == 0
			&& (current->str[ft_strlen(var_name)] == '=' 
			|| current->str[ft_strlen(var_name)] == '\0'))
		{
			free(current->str);
			current->str = ft_strdup(new_env_var);
			if (!current->str)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	
	return (EXIT_SUCCESS);
}
bool 	get_my_env(t_env *env, char *var_name)
{
	t_env *current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->str, var_name, ft_strlen(var_name)) == 0
			&& (current->str[ft_strlen(var_name)] == '='
			|| current->str[ft_strlen(var_name)] == '\0'))
			return (true);
		current = current->next;
	}
	
	return (false);
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