/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/20 13:14:44 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tokenisation(t_data *data, char *input)
{
	uint8_t		token;
	size_t		i;
	
	i = 0;
	while (i < ft_strlen(input))
	{	
		token = 0;
		if (handle_str(data, input, &token, &i))
			return (EXIT_FAILURE);
		if (handle_special_char(data, input, &token, &i))
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}