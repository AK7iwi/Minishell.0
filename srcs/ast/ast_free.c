/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:15:11 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/24 18:26:00 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_cmd(t_cmd *cmd)
{
	size_t i;
	
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}

	free(cmd->args);
	cmd->args = NULL; 
}

static void free_operator(t_operator *op)
{
    if (op->left)
        free_ast(&op->left);
    if (op->right)
        free_ast(&op->right);
}

void free_ast(t_ast **ast)
{
	if ((*ast)->type == AST_OPERATOR)
		free_operator(&(*ast)->operator);
	else if ((*ast)->type == AST_COMMAND)
		free_cmd(&(*ast)->cmd);

	free(*ast);
	*ast = NULL; 
}
