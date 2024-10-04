/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthesis_analysis_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:40:57 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/26 14:09:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_open_paren(t_tok_type type)
{
	return (type == TOKEN_OPEN_PAREN);
}
inline bool is_closed_paren(t_tok_type type)
{
	return (type == TOKEN_CLOSE_PAREN);
}
inline bool is_or(t_tok_type type)
{
	return (type == TOKEN_OR);
}

inline bool is_and(t_tok_type type)
{
	return (type == TOKEN_AND);	
}
inline bool is_pipe(t_tok_type type)
{
	return (type == TOKEN_PIPE);
}