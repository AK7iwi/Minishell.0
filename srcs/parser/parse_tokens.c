/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/16 16:45:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool 		check_paren(t_token *current, uint64_t *o_counter, uint64_t *c_counter)
{
	if (current->type == TOKEN_OPEN_PAREN)
		(*o_counter)++;
	else if (current->type == TOKEN_CLOSE_PAREN)
		(*c_counter)++;
	
	if (c_counter > o_counter)
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

static bool check_redir(t_token *current)
{
	return ((current->type == TOKEN_SIMPLE_REDIRECT_IN 
		|| current->type == TOKEN_SIMPLE_REDIRECT_OUT 
		|| current->type == TOKEN_DOUBLE_REDIRECT_IN 
		|| current->type == TOKEN_DOUBLE_REDIRECT_OUT)
		&& (!current->next || current->next->type != TOKEN_WORD));
}

static bool check_separator(t_token *current)
{	
	return ((current->type == TOKEN_PIPE 
			|| current->type == TOKEN_AND 
			|| current->type == TOKEN_OR) 
			&& (!current->prev || current->prev->type != TOKEN_WORD));
}

bool parse_tokens(t_data *data)
{
    t_token		*current;
	uint64_t	o_counter;
	uint64_t	c_counter;
	
	o_counter = 0;
	c_counter = 0;

    current = data->token;
    while (current)
    {
		if (check_separator(current))
			return (data->error.error_g |= ERROR_PIPE, EXIT_FAILURE);
		else if (check_redir(current))
			return (data->error.error_g |= ERROR_REDIR, EXIT_FAILURE);	
		else if (check_paren(current, &o_counter, &c_counter))
			return (data->error.error_g |= ERROR_PARAN, EXIT_FAILURE);
		
        current = current->next;
    }
	
	if (o_counter != c_counter)
		return (data->error.error_g |= ERROR_PARAN, EXIT_FAILURE);
	
    return (EXIT_SUCCESS);
}


