/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:16:12 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/04 09:52:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_env(t_data *data, char **envp)
{
    size_t i;

	i = 0;
    while (envp[i]) 
    {
		if (add_env_var(&data->env, envp[i]))
			return (data->error.gen_errors |= ERROR_MALLOC, EXIT_FAILURE);
        i++;
    }

	return (EXIT_SUCCESS);
}