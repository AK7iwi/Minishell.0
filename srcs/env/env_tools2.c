/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:39:28 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/10 10:39:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env_node(t_env **env, t_env *to_remove)
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
