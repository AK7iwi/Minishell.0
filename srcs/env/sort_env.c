/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:49:43 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/08 12:18:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env_array)
{
    size_t i;
    size_t j;

	i = 0;
	j = 0;
	
    while (env_array[i - 2])
    {
		if (strcmp(env_array[i][0], env_array[i][1]) > 0)
        	ft_swap(&env_array[i], &env_array[i + 1]);
		i++;
    }
}
char	**copy_env(t_env *env)
{
    char **env_array;
	t_env *current;
    uint32_t count;
	
	current = env;
	count = 0;
    while (current) 
    {
        count++;
        current = current->next;
    }
	
	env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);

    current = env;
    count = 0;
    while (current)
    {
        env_array[count++] = current->str;
        current = current->next;
    }
    env_array[count] = NULL;
	return (env_array);
}