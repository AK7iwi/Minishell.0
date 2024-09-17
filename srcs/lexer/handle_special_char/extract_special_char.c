/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_special_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:03:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/17 16:04:15 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' 
			|| input[*i] == '<' 
			|| input[*i] == '>' 
			|| input[*i] == '&' 
			|| input[*i] == '(' 
			|| input[*i] == ')'); //|| input[*i] == '*')
}

char *extract_special_char(t_data *data, char *input, size_t *i)
{
	char *str;
	size_t len;

	str = NULL;
	len = 0;
	size_t j = 0;
	size_t start;
	start = (*i);
	char special_char;

	special_char = '\0';

	if (is_special_char(input, i))
	{
		special_char = input[*i];
		(*i)++;
		if (input[*i] == special_char && input[*i] != '(' && input[*i] != ')')
		{
			(*i)++;
			len = 2;
		}
		else 
			len = 1;
	}

	str = malloc(len + 1);
	if (!str)
		return (data->error.error_g |= ERROR_MALLOC, NULL);

	while (start < (*i))
		str[j++] = input[start++];

	str[j] = '\0';
	
	return (str);
}