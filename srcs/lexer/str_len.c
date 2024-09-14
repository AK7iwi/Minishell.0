/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:20:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/14 17:55:02 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_quotes_len(char *input, ssize_t *str_len, uint8_t *t, size_t *i)
{
	char quote_char;

	quote_char = '\0';

	if ((input[*i] == '\'' || input[*i] == '\"')) 
    {
        quote_char = input[*i];
        (*i)++;
        while (input[*i] != quote_char && input[*i] != '\0')
        {
			if (input[*i] == '$' && quote_char == '\"')
				(*t) = TOKEN_ENV_VAR;
			(*str_len)++;
            (*i)++;
        }
		(*str_len)--; //find a cleaner way 
        if (input[*i] != quote_char) //verif if open quote
			return (1);
    }
	
	return (0);
}

ssize_t handle_str_len(char *input, uint8_t *token, size_t *i)
{
    ssize_t	str_len;

	str_len = 0;
	
    while (input[*i] != ' ' && input[*i] != '\0')
    {
		if (handle_quotes_len(input, &str_len, token, i))
			return (-1);
		if (input[*i] == '$')
			(*token) = TOKEN_ENV_VAR;
		else
        	str_len++;
		(*i)++;
	}
	
    return (str_len);
}