/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:07:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 22:10:52 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool handle_str(t_data *data, char *input, uint8_t *token, size_t *index)
{
	char 		*str_token;

	str_token = extract_str(&data->error, input, token, index);
	if (!str_token)
		return (EXIT_FAILURE);
	if (!(*token))
		(*token) = TOKEN_WORD;
	if (add_token(&data->token, token, str_token))
		return (data->error.error_g |= ERROR_MALLOC, EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}