/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/27 12:01:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool syn_analyzer(t_data *data)
{
    t_token		*current;
	uint32_t	o_counter;
	uint32_t	c_counter;
	
	o_counter = 0;
	c_counter = 0;
    current = data->token;
	
    while (current)
    {
		if (operator_checker(current))
			return (data->error.error_g |= ERROR_OPERATOR, EXIT_FAILURE);
		else if (redir_checker(current))
			return (data->error.error_g |= ERROR_REDIR, EXIT_FAILURE);	
		else if (paren_checker(current, &o_counter, &c_counter))
			return (data->error.error_g |= ERROR_PARAN, EXIT_FAILURE);
		current = current->next;
    }
	
	if (o_counter != c_counter)
		return (data->error.error_g |= ERROR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


