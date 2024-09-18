/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/18 13:24:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_special_char(t_data *data, char *input, uint8_t *token, size_t *index)
{
	char *str_token;
	
	str_token = extract_special_char(data, input, index);
	if (!str_token)
		return (EXIT_FAILURE);
	
	(*token) = wich_token(str_token);
	if (add_token(&data->token, token, str_token))
		return (data->error.error_g |= ERROR_MALLOC, EXIT_FAILURE);
		
	return (EXIT_SUCCESS);
}