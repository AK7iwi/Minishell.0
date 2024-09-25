/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:24:08 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 20:40:25 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_subsh_node(t_token **current)
{
	t_ast 		*new_node;
	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	new_node->type = AST_SUBSH;
	printf("Create subshell\n");
	(*current) = (*current)->next;
    new_node->subshell.root = ast_algo((*current), 0);
	if (new_node->subshell.root)
	{
		printf ("AST2:\n");
		print_ast(new_node->subshell.root, 0);
	}
	while((*current)->type != TOKEN_CLOSE_PAREN)
		(*current) = (*current)->next;
	(*current) = (*current)->next;
	return (new_node);
}