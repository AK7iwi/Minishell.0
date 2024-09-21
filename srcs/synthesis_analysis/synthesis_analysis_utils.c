/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthesis_analysis_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:17:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 13:44:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_cmd(uint8_t type)
{
	return (!is_operator(type) 
		&& !is_closed_paren(type) 
		&& !is_open_paren(type));
}
inline bool is_redir(uint8_t type)
{
	return (type == TOKEN_SIMPLE_REDIRECT_OUT 
		|| type == TOKEN_DOUBLE_REDIRECT_OUT
		|| type == TOKEN_SIMPLE_REDIRECT_IN
		|| type == TOKEN_DOUBLE_REDIRECT_IN);
}
inline bool is_operator(uint8_t type)
{
	return ((is_pipe(type) 
		|| is_and(type) 
		|| is_or(type)));
}