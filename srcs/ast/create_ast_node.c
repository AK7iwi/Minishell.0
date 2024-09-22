/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/22 18:24:29 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_cmd_len(t_token *current)
{
	size_t cmd_len;
	t_token *temp;

	cmd_len = 0;
	temp = current;
	
    while (temp && is_arg_cmd(temp->type))
    {
        cmd_len++;
        temp = temp->next;
    } 

	return (cmd_len);
}

t_ast	*create_node_cmd(t_token **tokens)
{
	t_ast *new_node;
	size_t cmd_len;
	size_t i;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	cmd_len = get_cmd_len((*tokens));
	
	if (cmd_len)
	{
		new_node->type = AST_COMMAND;
		new_node->cmd.args = malloc((cmd_len + 1) * sizeof(char *));
		if (!new_node->cmd.args)
            return (NULL);
		
		i = 0;
		while (i < cmd_len)
		{
			new_node->cmd.args[i++] = ft_strdup((*tokens)->str); //protect
			(*tokens) = (*tokens)->next;
		}
		new_node->cmd.args[i] = NULL;
	}
	//else if cmd_len = 0;
	
	return (new_node);
}

t_ast	*create_operator_node(t_ast *left, t_ast *right, t_operator_type operator_type)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	new_node->type = AST_OPERATOR;
	new_node->operator.left = left;
	new_node->operator.right = right;
	// new_node->operator.left->left = NULL;
	// new_node->operator.left->right = NULL;
	// new_node->operator.right->left = NULL;
	// new_node->operator.right->right = NULL;
	new_node->operator.type = operator_type;
	
	return (new_node);
}