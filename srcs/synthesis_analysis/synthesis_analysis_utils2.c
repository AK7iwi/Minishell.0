/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthesis_analysis_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:40:57 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 13:47:28 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_open_paren(uint8_t type)
{
	return (type == TOKEN_OPEN_PAREN);
}
inline bool is_closed_paren(uint8_t type)
{
	return (type == TOKEN_CLOSE_PAREN);
}
inline bool is_or(uint8_t type)
{
	return (type == TOKEN_OR);
}

inline bool is_and(uint8_t type)
{
	return (type == TOKEN_AND);	
}
inline bool is_pipe(uint8_t type)
{
	return (type == TOKEN_PIPE);
}