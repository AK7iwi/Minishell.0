/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 18:19:11 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t get_cmd_len(t_token *current)
{
	size_t cmd_len;
	t_token *temp;

	cmd_len = 0;
	temp = current;
	
    while (temp && is_cmd(temp->type))
    {
        cmd_len++;
        temp = temp->next;
    } 

	return (cmd_len);
}

t_ast	*create_node_cmd(t_token **current)
{
	t_ast *new_node;
	size_t cmd_len;
	size_t i;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	cmd_len = get_cmd_len((*current));
	
	if (cmd_len > 0)
	{
		new_node->type = AST_COMMAND;
		new_node->cmd.args = malloc((cmd_len + 1) * sizeof(char *));
		if (!new_node->cmd.args)
            return (NULL);
		
		i = 0;
		while (i < cmd_len)
		{
			new_node->cmd.args[i++] = ft_strdup((*current)->str); //protect
			(*current) = (*current)->next;
		}
		new_node->cmd.args[i] = NULL;
	}
	
	return (new_node);
}

// void create_operator_node(t_data *data, t_token **current)
// {
// 	new_node->type = AST_OPERATOR;
// 	if (is_pipe((*current)->type))
// 		new_node->operator.type = AST_PIPE;	
// 	else if (is_and((*current)->type))
// 		new_node->operator.type = AST_AND;
// 	else if (is_or((*current)->type))
// 		new_node->operator.type = AST_OR;
// 	printf ("Operator elem:%d\n", new_node->operator.type);
// 		// (*current) = (*current)->next;
// }