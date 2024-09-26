/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 22:43:34 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_subshell(t_ast *ast, int *depth)
{
	printf("[Subshell]\n");
	for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
	print_ast(ast->subshell.root, (*depth));
}

void print_cmd(t_ast *ast)
{
	size_t i;

	i = 0;
	printf("[Cmd] ");
	while (ast->cmd.args[i])
	{
		printf("%s ", ast->cmd.args[i]);
		i++;
	}
	printf("\n");
}
void print_operator(t_ast *ast, int *depth)
{	
	printf("[Operator] ");
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
        printf("    [left] ");
        print_ast(ast->operator.left, (*depth) + 1);
    }

    if (ast->operator.right)
	{
		for (int i = 0; i < (*depth) + 1; i++)
			printf("\t");
        printf("    [right] ");
        print_ast(ast->operator.right, (*depth) + 1);
    }
}
void print_ast(t_ast *ast, int depth)
{
	t_ast *current = ast;
	
	if (current->type == AST_OPERATOR)
		print_operator(current, &depth);
	else if (current->type == AST_COMMAND)
		print_cmd(current);
	else if (current->type == AST_SUBSH)
		print_subshell(current, &depth);
}
