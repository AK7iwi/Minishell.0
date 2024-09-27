/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/27 13:11:07 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool exec_subshell(t_subshell *subsh)
{
	ast_exec(subsh->root);
	
	return (EXIT_SUCCESS);
}

static bool exec_cmd(t_cmd *cmd)
{
	// size_t i;
	
	// i = 0;
	// while (cmd->args[i])
	// {
	// 	//exec cmd
	// 	printf("%s ", cmd->args[i]);
	// 	i++;
	// }
	if (cmd->args[0] == "echo") // ft_strncmp
		echo(cmd->args);
	
	return (EXIT_SUCCESS);
	
}

static bool exec_operator(t_operator *op)
{
	if (op->left)
    	ast_exec(op->left);
    if (op->right)
        ast_exec(op->right);
	else
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
bool ast_exec(t_ast *root)
{
	if (root->type == AST_OPERATOR)
		exec_operator(&root->operator);
	else if (root->type == AST_COMMAND)
		exec_cmd(&root->cmd);
	else if (root->type == AST_SUBSH)
		exec_subshell(&root->subshell);
	
	return (EXIT_SUCCESS);
}
bool exec(t_data *data)
{
	t_ast *root;
	
	root = data->ast;
	if (ast_exec(root))
		return (EXIT_FAILURE);
	
	return (EXIT_FAILURE);
}