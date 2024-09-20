/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/20 13:41:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_cmd(t_data *data, t_token *current)
{
	uint8_t type;

	type = current->type;
	(void)data;
	printf ("FILL CMD:\n");
	if (!is_operator(type) && !is_redir(type) && !is_closed_paren(type) && !is_open_paren(type))
		printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
}