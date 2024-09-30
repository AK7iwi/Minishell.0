/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/30 10:55:50 by mfeldman         ###   ########.fr       */
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
	if (data->env)
		free_env(&data->env);
}

//maybe need later for env_var

// void	free_all(t_data *data)
// {
// 	printf("Free all:\n");
// 	if (data->token)
// 	{
// 		printf("Free token\n");
// 		free_token(&data->token);
// 	}
// 	if (data->ast)
// 	{
// 		printf("Free AST\n");
// 		free_ast(&data->ast);
// 	}
// }