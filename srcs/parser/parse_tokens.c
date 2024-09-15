/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 17:01:22 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool check_separators(t_token *current)
{
	return (!current->next || current->next->type != TOKEN_WORD);
}

static inline bool is_separator(uint8_t type)
{
	return (type == TOKEN_SIMPLE_REDIRECT_IN 
		|| type == TOKEN_SIMPLE_REDIRECT_OUT 
		|| type == TOKEN_DOUBLE_REDIRECT_IN 
		|| type == TOKEN_DOUBLE_REDIRECT_OUT);
}

static inline bool check_pipe(t_token *current)
{
	return (!current->prev || current->prev->type != TOKEN_WORD);
}

bool parse_tokens(t_data *data)
{
    t_token *current;

    current = data->token;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
		{
			if (check_pipe(current))
				return (data->error.error_g |= ERROR_PIPE, EXIT_FAILURE);
		}
        else if (is_separator(current->type))
		{
			if (check_separators(current))
				return (data->error.error_g |= ERROR_REDIR, EXIT_FAILURE);
		}
			
        current = current->next;
    }
    return (EXIT_SUCCESS);
}