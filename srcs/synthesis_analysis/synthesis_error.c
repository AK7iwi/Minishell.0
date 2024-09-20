/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:09:55 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/20 13:24:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_paren(t_token *current, uint64_t *o_counter, uint64_t *c_counter)
{
	if (is_open_paren(current->type))
		(*o_counter)++;
	else if (is_closed_paren(current->type))
		(*c_counter)++;
	
	if (c_counter > o_counter)
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

bool check_redir(t_token *current)
{
	return (is_redir(current->type)
		&& (!current->next || current->next->type != TOKEN_WORD));

}
bool check_operator(t_token *current)
{	
	return (is_operator(current->type)
			&& ((!current->prev || current->prev->type != TOKEN_WORD) 
			|| (!current->next || current->next->type != TOKEN_WORD)));
}