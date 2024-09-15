/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 16:41:53 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool check_separators()
{
	return (!current->next || current->next->type != TOKEN_WORD)
}

static inline bool is_separator(uint8_t type)
{
	return (current->type == TOKEN_SIMPLE_REDIRECT_IN 
		|| current->type == TOKEN_SIMPLE_REDIRECT_OUT 
		|| current->type == TOKEN_DOUBLE_REDIRECT_IN 
		|| current->type == TOKEN_DOUBLE_REDIRECT_OUT);
}

static inline bool check_pipe()
{
	return (!current->prev || current->prev->type != TOKEN_WORD);
}

bool parse_tokens(t_token **tokens)
{
    t_token *current;

    current = *tokens;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
			if (check_pipe())
				return (false);
                printf("Syntax error: invalid use of pipe\n");
        else if (is_separator(current->type)) 
			if (check_separators())
				return (false);
        current = current->next;
    }
    return (true);
}