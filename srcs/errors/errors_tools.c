/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 08:49:25 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/04 10:44:45 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	free_errors(t_error *error)
{
	error->gen_errors = 0;
	error->parsing_errors = 0;
	error->exec_errors = 0;
}