/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:16:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/28 12:20:48 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool is_builtins(C)
{
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
		echo(cmd->args);
	
	
}