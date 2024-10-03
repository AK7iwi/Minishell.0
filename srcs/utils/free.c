/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/03 18:50:50 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(t_data *data)
{
	if (data->error.error_g)
		free_error(&data->error);
	if (data->token)
		free_token(&data->token);
	if (data->ast)
		ast_freer(&data->ast);
	// if (data->env)
	// 	free_env(&data->env);
}