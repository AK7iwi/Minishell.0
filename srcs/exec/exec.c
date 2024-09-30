/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/30 12:47:31 by mfeldman         ###   ########.fr       */
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
	if (is_builtins(cmd->args))
		return (EXIT_SUCCESS);
	
	return (EXIT_FAILURE);
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

//use data
bool exec(t_data *data, char **envp)
{
	t_ast *root;
	
	if (init_env(data, envp))
		return (EXIT_FAILURE);
	
	root = data->ast;
	if (ast_exec(root))
		return (EXIT_FAILURE);
	
	return (EXIT_FAILURE);
}