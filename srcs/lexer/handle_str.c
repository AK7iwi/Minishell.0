/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/13 18:45:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool handle_quotes(char *input, char **str, bool *open_quote, size_t *str_start, size_t *i, uint8_t ***token)
{
	char quote_char;

	quote_char = '\0';
	
	if ((input[*str_start] == '\'' || input[*str_start] == '\"') && !(*open_quote)) 
    {
		(*open_quote) = true;
		quote_char = input[*str_start];
       	(*str_start)++;
        while (input[*str_start] != quote_char && input[*str_start] != '\0')
		{
			if (input[*str_start] == '$')
				(***token) = TOKEN_ENV_VAR;
			**str[(*i)] = input[*str_start];
            (*str_start)++;
			(*i)++;
		}
        if (input[*str_start] == quote_char)
			(*open_quote) = false;
		else
			return (0);
    }
	
	return (1);
}

static char* copy_str(char *input, size_t str_start, size_t **str_end, size_t str_len)
{
	char *str;
	bool open_quote;
	size_t i;
	
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	
	open_quote = false;
	i = 0;
	
	while (str_start < (**str_end))
	{
		// if (handle_quotes(input, &str, &open_quote, &str_start, &i, &token))
		// 	return (NULL);
		// else
		// {
		// 	if (input[str_start] == '$')
		// 		(**token) = TOKEN_ENV_VAR;
		// }
		str[i++] = input[str_start];
		str_start++;	
	}
	
	str[i] = '\0';
	
	return (str);
}

static size_t skip_space(char *input, size_t **i)
{
	while (input[**i] == ' ')
		(**i)++;

	return (**i);
}

char*	extract_str(char *input, uint8_t *token, size_t *index)
{
	size_t 	str_start;
	size_t	str_len;
	char*	str;
	
	str_start = skip_space(input, &index);
	printf("Index value: %li\n", (*index));
	str_len = handle_str_len(input, &index); //protect
	printf("Index value: %li\n", (*index)); 
	
	printf("len of str: %li\n", str_len);	
	(void)token;
	str = copy_str(input, str_start, &index, str_len); //protect 
	
	return (str);
}