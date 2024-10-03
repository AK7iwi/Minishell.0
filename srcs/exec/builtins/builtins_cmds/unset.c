/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:45:10 by diguler           #+#    #+#             */
/*   Updated: 2024/09/28 12:45:22 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env_node(t_env_list **env, t_env_list *to_remove)
{
    if (to_remove->prev)
        to_remove->prev->next = to_remove->next;
    if (to_remove->next)
        to_remove->next->prev = to_remove->prev;

    if (to_remove == *env)
        *env = to_remove->next;

    free(to_remove->str);
    free(to_remove);
}

int unset_variable(t_env_list **env, char *var)
{
    t_env_list *current = *env;

    while (current)
    {
        if (strncmp(current->str, var, strlen(var)) == 0 && current->str[strlen(var)] == '=')
        {
            remove_env_node(env, current);
            return (1); 
        }
        current = current->next;
    }
    return (0); 
}

void unset(char **args, t_env_list **env)
{
    int i = 1;
    int found;

    if (!args[1])
    {
        printf("unset: not enough arguments\n");
        return;
    }
    while (args[i])
    {
        found = unset_variable(env, args[i]);
        if (!found)
            printf("unset: '%s': variable not found\n", args[i]);
        i++;
    }
}

