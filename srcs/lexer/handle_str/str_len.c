/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:20:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/18 13:32:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_quotes_len(char *input, ssize_t *str_len, uint8_t *t, size_t *i)
{
	char quote_char;

	quote_char = '\0';

	if ((input[*i] == S_QUOTE || input[*i] == D_QUOTE)) 
    {
        quote_char = input[*i];
        (*i)++;
        while (input[*i] != quote_char && input[*i] != NULL_CHAR)
        {
			if (input[*i] == '$' && quote_char == '\"')
				(*t) = TOKEN_ENV_VAR;
			(*str_len)++;
            (*i)++;
        }
		(*str_len)--;
        if (input[*i] != quote_char) //verif if open quote
			return (EXIT_FAILURE);
    }
	
	return (EXIT_SUCCESS);
}
ssize_t	get_str_len(char *input, uint8_t *token, size_t *i)
{
    ssize_t	str_len;

	str_len = 0;
	
    while (!is_special_char(input, i) && input[*i] != SPACE && input[*i] != NULL_CHAR)
    {
		if (get_quotes_len(input, &str_len, token, i))
			return (-1);
		if (input[*i] == '$')
			(*token) = TOKEN_ENV_VAR;
		else
        	str_len++;
		(*i)++;
	}

    return (str_len);
}