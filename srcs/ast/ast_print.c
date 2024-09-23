/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/23 19:06:14 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd(t_ast *ast, int *depth)
{
	size_t i;

	i = 0;

	for (int i = 0; i < (*depth) ; i++)
		printf("\t");
		
	while (ast->cmd.args[i])
	{
		printf("%s ", ast->cmd.args[i]);
		i++;
	}
	printf("\n");
}

void print_operator(t_ast *ast, int *depth)
{
    for (int i = 0; i < (*depth); i++)
		printf("\t");
	
    if (ast->operator.type == AST_PIPE)
		printf("|\n");
	else if (ast->operator.type == AST_AND)
		printf("&&\n");
	else if (ast->operator.type == AST_OR)
		printf("||\n");

    if (ast->operator.left)
	{
        print_ast(ast->operator.left, (*depth) + 1);
    }

    if (ast->operator.right)
	{
        print_ast(ast->operator.right, (*depth) + 1);
    }
}

void print_ast(t_ast *ast, int depth)
{
	if (ast->type == AST_COMMAND)
		print_cmd(ast, &depth);
	else if (ast->type == AST_OPERATOR)
		print_operator(ast, &depth);
}
