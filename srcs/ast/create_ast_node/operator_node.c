/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:29:19 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 12:32:24 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_operator_node(t_ast *left, t_ast *right, t_op_type op_type)
{
	t_ast *new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	new_node->type = AST_OPERATOR;
	new_node->operator.type = op_type;
	new_node->operator.left = left;
	new_node->operator.right = right;
	
	return (new_node);
}