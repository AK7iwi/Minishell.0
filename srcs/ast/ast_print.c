/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:57:33 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/22 19:52:14 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_ast(t_ast *ast, size_t depth)
// {
// 	size_t i;

// 	i = 0;

// 	if (!ast)
// 		return ;
	
// 	while (i++ < depth * 2)
// 		write(1, "    ", 4);
	
// 	i = 0;
// 	if (ast->type == AST_COMMAND)
// 	{
// 		while (ast->cmd.args[i])
// 		{
// 			printf("cmd elem:%s\n", ast->cmd.args[i]);
// 			i++;
// 		}
// 	}
// 	else if (ast->type == AST_OPERATOR)
// 	{
// 		if (ast->operator.type == AST_PIPE)
// 			printf("|\n");
// 		else if (ast->operator.type == AST_AND)
// 			printf("&&\n");
// 		else if (ast->operator.type == AST_OR)
// 			printf("||\n");
// 		print_ast(ast->operator.left, depth + 1);
// 		print_ast(ast->operator.right, depth + 1);
// 	}
// }

#include <stdio.h>

void print_cmd(t_cmd *cmd) {
    if (cmd->args) {
        // Print command arguments on one line
        for (int i = 0; cmd->args[i]; i++) {
            printf("%s ", cmd->args[i]);
        }
        printf("\n");
    }
}

void print_operator(t_operator *op, int depth) {
    // Indentation based on tree depth
    for (int i = 0; i < depth; i++) printf("\t");

    printf("|\n");

    // Print left subtree (e.g., the command on the left side of the pipe)
    if (op->left) {
        for (int i = 0; i < depth; i++) printf("\t");
        printf("/ \\\n");
        print_ast(op->left, depth + 1);
    }

    // Print right subtree (e.g., the command on the right side of the pipe)
    if (op->right) {
        print_ast(op->right, depth + 1);
    }
}

// void print_subshell(t_subshell *subshell, int depth) {
//     if (subshell->root) {
//         print_ast(subshell->root, depth);
//     }
// }

void print_ast(t_ast *node, int depth)
{
    if (!node) {
        printf("Empty node\n");
        return;
    }

    switch (node->type) {
        case AST_COMMAND:
            for (int i = 0; i < depth; i++) printf("\t");  // Indentation
            print_cmd(&node->cmd);
            break;
        case AST_OPERATOR:
            print_operator(&node->operator, depth);
            break;
        default:
            printf("Unknown AST node type\n");
            break;
    }
}
