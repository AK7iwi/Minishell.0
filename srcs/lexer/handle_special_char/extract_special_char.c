/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_special_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:03:10 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/18 12:00:02 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char* copy_special_char(char *input, size_t start, size_t *end, size_t len)
{
	char *str;
	size_t i;

	i = 0;

	str = malloc(len + 1);
	if (!str)
		return (NULL);

	while (start < (*end))
		str[i++] = input[start++];

	str[i] = '\0';

	return (str);
}

bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' 
			|| input[*i] == '<' 
			|| input[*i] == '>' 
			|| input[*i] == '&' 
			|| input[*i] == '(' 
			|| input[*i] == ')');
}
char *extract_special_char(t_data *data, char *input, size_t *index)
{
	char *str;
	size_t start;
	size_t len;
	
	start = (*index);
	len = get_special_char_len(input, index);
	str = copy_special_char(input, start, index, len);
	if (!str)
		return (data->error.error_g |= ERROR_MALLOC, NULL);
	
	return (str);
}