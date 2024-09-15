/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:02:32 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 14:00:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_syntax_errors(t_token **tokens)
{
    t_token *current;

    current = *tokens;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (!current->prev || current->prev->type != TOKEN_WORD)
            {
                printf("Syntax error: invalid use of pipe\n");
                return (false);
            }
        }
        else if (current->type == TOKEN_SIMPLE_REDIRECT_IN 
				|| current->type == TOKEN_SIMPLE_REDIRECT_OUT 
				|| current->type == TOKEN_DOUBLE_REDIRECT_IN 
				|| current->type == TOKEN_DOUBLE_REDIRECT_OUT)
        {
            if (!current->next || current->next->type != TOKEN_WORD)
            {
                printf("Syntax error: invalid use of redirection\n");
                return (false);
            }
        }
        current = current->next;
    }
    return (true);
}