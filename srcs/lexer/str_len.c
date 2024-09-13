/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:20:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/13 18:07:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_quotes_len(char *input, bool *open_quote, size_t ***i, size_t *len)
{
	char quote_char;

	quote_char = '\0';

	if ((input[***i] == '\'' || input[***i] == '\"') && !(*open_quote)) 
    {
		(*open_quote) = true;
        quote_char = input[***i];
        (***i)++;
        while (input[***i] != quote_char && input[***i] != '\0')
        {
			(*len)++;
            (***i)++;
        }
	
        if (input[***i] == quote_char)
			(*open_quote) = false;
		else
			return (0);
    }

	return (1);
}

size_t handle_str_len(char *input, size_t **i)
{
	bool	open_quote;
    size_t	len;

	open_quote = false;
	len = 0;
	
    while (input[**i] != ' ' && input[**i] != '\0')
    {
		if (!handle_quotes_len(input, &open_quote, &i, &len))
			return (-1);
		else
            len++;
		(**i)++;
	}
	
    return (len);
}