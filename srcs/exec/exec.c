/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:38:35 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/05 15:50:09 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool exec_subshell(t_data *data, t_subshell *subsh)
{
	ast_exec(data, subsh->root);
	
	return (EXIT_SUCCESS);
}

static bool exec_cmd(t_data *data, t_cmd *cmd)
{	
	if (is_builtins(data, cmd->args))
		return (EXIT_SUCCESS);
	//is_cmd
	
	return (EXIT_FAILURE);
}
static bool exec_operator(t_data *data, t_operator *op)
{
	if (op->left)
    	ast_exec(data, op->left);
    if (op->right)
        ast_exec(data, op->right);
	else
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}
bool ast_exec(t_data *data, t_ast *ast)
{
	t_ast *root;
	root = ast;

	//to protect
	if (root->type == AST_OPERATOR)
		exec_operator(data, &root->operator);
	else if (root->type == AST_COMMAND)
		exec_cmd(data, &root->cmd);
	else if (root->type == AST_SUBSH)
		exec_subshell(data, &root->subshell);
	
	return (EXIT_SUCCESS);
}