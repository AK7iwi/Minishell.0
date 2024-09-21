/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:37:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 16:37:41 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline bool is_cmd(uint8_t type)
{
	return (!is_operator(type) 
		&& !is_closed_paren(type) 
		&& !is_open_paren(type));
}
