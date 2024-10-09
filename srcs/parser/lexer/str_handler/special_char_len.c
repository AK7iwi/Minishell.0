/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:59:36 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 21:37:43 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t get_special_char_len(char *input, size_t *i)
{
	size_t len;
	char special_char;
	
	len = 0;
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

	return (len);
}