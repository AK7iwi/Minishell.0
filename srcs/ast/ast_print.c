/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/22 18:36:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_ast(t_data *data)
{
	t_ast *ast;

	ast = data->ast;
	
	if (ast->operator.type == AST_PIPE)
	{
		printf("|\n");
		printf("%s", ast->operator.left->cmd.args[0]);
		printf("%s", ast->operator.left->cmd.args[1]);
	}
	if (ast->operator.type == AST_AND)
		printf ("&&\n");
	if (ast->operator.type == AST_OR)
		printf ("||\n");
	
	if (ast->type == AST_COMMAND)
	{
		size_t i = 0;

		while (ast->cmd.args[i])
		{
			printf ("cmd[%li]:%s\n",i, ast->cmd.args[i]);
			i++;
		}
	}

	// printf("Operator%i:\n", ast->operator.type);
}