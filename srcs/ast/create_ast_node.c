/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/24 18:57:23 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_operator_node(t_ast *left, t_ast *right, t_operator_type operator_type)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	new_node->type = AST_OPERATOR;
	new_node->operator.type = operator_type;
	new_node->operator.left = left;
	new_node->operator.right = right;
	
	return (new_node);
}

static char **copy_args(t_token **current, size_t cmd_len)
{
	char **args;
	size_t i;
	
	args = malloc((cmd_len + 1) * sizeof(char *));
	if (!args)
        return (NULL);
	i = 0;
	while (i < cmd_len)
	{
		args[i++] = ft_strdup((*current)->str); //protect
		(*current) = (*current)->next;
	}
	args[i] = NULL;
	
	return (args);
}
static size_t get_cmd_len(t_token *current)
{
	size_t cmd_len;

	cmd_len = 0;
	
    while (current && is_arg_cmd(current->type))
    {
        cmd_len++;
        current = current->next;
    } 

	return (cmd_len);
}

t_ast	*create_node_cmd(t_token **current)
{
	t_ast *new_node;
	size_t cmd_len;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	cmd_len = get_cmd_len((*current));
	if (cmd_len <= 0)
		return (NULL);
	
	new_node->type = AST_COMMAND;
	new_node->cmd.args = copy_args(current, cmd_len);
	
	return (new_node);
}