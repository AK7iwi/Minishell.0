/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/22 14:35:36 by mfeldman         ###   ########.fr       */
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
			|| input[*i] == ')');
}
bool handle_special_char(t_data *data, char *input, uint8_t *token, size_t *index)
{
	char *str_token;
	
	str_token = extract_special_char(data, input, index); //t_error
	if (!str_token)
		return (EXIT_FAILURE);
	
	(*token) = wich_token(str_token);
	if (add_token(&data->token, token, str_token))
		return (data->error.error_g |= ERROR_MALLOC, EXIT_FAILURE);
		
	return (EXIT_SUCCESS);
}