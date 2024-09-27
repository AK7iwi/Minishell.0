/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/27 12:08:25 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*subsh_node_creator(t_ast **new_node, t_token **current)
{
	(*new_node)->type = AST_SUBSH;
	(*current) = (*current)->next;
    (*new_node)->subshell.root = ast_algo(current, 0);
	while((*current)->type != TOKEN_CLOSE_PAREN)
		(*current) = (*current)->next;
	(*current) = (*current)->next;
	
	return ((*new_node));
}