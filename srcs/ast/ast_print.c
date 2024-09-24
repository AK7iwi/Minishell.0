/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/24 18:26:50 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd(t_ast *ast)
{
	size_t i;

	i = 0;
	while (ast->cmd.args[i])
	{
		printf("%s ", ast->cmd.args[i]);
		i++;
	}
	printf("\n");
}

void print_operator(t_ast *ast, int *depth)
{	
	printf("[Operator]: ");
    if (ast->operator.type == AST_PIPE)
		printf("'|'");
	else if (ast->operator.type == AST_AND)
		printf("'&&'");
	else if (ast->operator.type == AST_OR)
		printf("'||'");
	
	printf("\n");
    if (ast->operator.left)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [left]: ");
        print_ast(ast->operator.left, (*depth) + 1);
    }

    if (ast->operator.right)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [right]: ");
        print_ast(ast->operator.right, (*depth) + 1);
    }
}
void print_ast(t_ast *ast, int depth)
{
	if (ast->type == AST_OPERATOR)
		print_operator(ast, &depth);
	else if (ast->type == AST_COMMAND)
		print_cmd(ast);
}
