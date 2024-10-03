/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:18:51 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/03 20:13:38 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init(t_data *data, char **argv, char **envp)
{
	(void)argv;
	data->error.error_gen = 0;
	data->error.error_parsing = 0;
	data->error.error_exec = 0;
	data->token = NULL;
	data->ast = NULL;
	data->env = NULL;

	return (init_env(data, envp));
}