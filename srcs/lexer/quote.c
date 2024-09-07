/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:00:47 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/07 16:23:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_open_dquote(char *line)
{
	int i;

	i = 0;

	while (line[i])
	{
		if (line[i] == '\"')
			return (true);
		i++;
	}
		
	return (false);
}