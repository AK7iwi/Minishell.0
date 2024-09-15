/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:21:27 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 17:49:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	handle_quotes(char *input, char *str, size_t *start, size_t *i)
{
	char	quote_char;

	quote_char = '\0';
	if ((input[*start] == '\'' || input[*start] == '\"'))
    {
		quote_char = input[*start];
       	(*start)++;
        while (input[*start] != quote_char && input[*start] != '\0')
		{
			str[(*i)] = input[*start];
            (*start)++;
			(*i)++;
		}
		return (1);
    }
	
	return (0);
}

static char* copy_str(char *input, size_t start, size_t *end, size_t len)
{
	char *str;
	size_t i;
	
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	
	i = 0;
	while (start < (*end))
	{
		if (handle_quotes(input, str, &start, &i))
			start++;
		else 
			str[i++] = input[start++];	
	}
	
	str[i] = '\0';
	
	return (str);
}

static size_t skip_space(char *input, size_t *i)
{
	while (input[*i] == ' ')
		(*i)++;

	return (*i);
}

char*	extract_str(char *input, uint8_t *token, size_t *index)
{
	size_t 	str_start;
	ssize_t	str_len;
	char*	str;
	
	str_start = skip_space(input, index);
	str_len = handle_str_len(input, token, index);
	if (str_len < 0)
		return (NULL); //error quote 

	str = copy_str(input, str_start, index, str_len);
	if (!str)
		return (NULL); //error_malloc
	
	return (str);
}