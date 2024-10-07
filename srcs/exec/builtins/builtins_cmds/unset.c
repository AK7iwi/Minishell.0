/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:45:10 by diguler           #+#    #+#             */
/*   Updated: 2024/10/07 09:17:02 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool unset(t_data *data, char **args)
{
    size_t i;

    if (!args[1])
        return (data->error.exec_errors |= ERROR_UNSET, EXIT_FAILURE);
	
	i = 1;
    while (args[i])
    {
        unset_variable(&data->env, args[i]); //no error msg in bash posix if env_var doesnt exist
        i++;
    }

	return (EXIT_SUCCESS);
}

