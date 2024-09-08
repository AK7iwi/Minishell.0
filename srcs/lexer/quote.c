/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:00:47 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/08 17:16:31 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extract_str_from_quotes(char *line, bool handle_quotes)
{
	size_t i;
	size_t len;
	int j;
	char *str;
	char quote;
	
	i = 0;
	len = 0;
	
	if (handle_quotes == S_QUOTE)
		quote = '\'';
	else if (handle_quotes == D_QUOTE)
		quote = '\"';
	
	while (i < ft_strlen(line))
	{
		if (line[i] == quote)
		{
			i++;
			while (line[i] != quote && line[i] != '\0')
			{
				len++;
				i++;
			}
		}
		i++;
	}
	
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);

	i = 0;
	j = 0;
	
	while (i < ft_strlen(line))
	{
		if (line[i] == quote)
		{
			i++;
			while (line[i] != quote && line[i] != '\0')
				str[j++] = line[i++];
		}
		i++;
	}
	
	str[j] = '\0';
	
	return (str);
}

uint8_t	find_open_quote(char *line)
{
	int i;

	i = 0;

	while (line[i])
	{
		if (line[i] == '\'')
			return (S_QUOTE);
		else if (line[i] == '\"')
			return (D_QUOTE);
		i++;
	}
		
	return (2);
}