/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/23 18:27:14 by mfeldman         ###   ########.fr       */
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

	for (int i = 0; i < (*depth) ; i++)
			printf("\t");
        printf("/ \\\n");
    if (ast->operator.left)
	{
		printf("A gauche:");
        print_ast(ast->operator.left, (*depth) + 2);
    }

    if (ast->operator.right)
	{
		printf("A droite:");
        print_ast(ast->operator.right, (*depth) + 2);
    }
}

void print_ast(t_ast *ast, int depth)
{
	if (ast->type == AST_COMMAND)
		print_cmd(ast, &depth);
	else if (ast->type == AST_OPERATOR)
		print_operator(ast, &depth);
}
