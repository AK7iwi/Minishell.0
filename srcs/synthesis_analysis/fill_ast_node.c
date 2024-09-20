/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:29 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/20 16:05:55 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_ast_node(t_data *data, t_token **current)
{
	t_ast *new_node;
	t_token *temp;
	size_t nb_args;
	size_t i;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return ;
	
	(void)data;
	nb_args = 0;
	temp = (*current); 
    while (temp && is_cmd(temp->type))
    {
        nb_args++;
        temp = temp->next;
    }
	
	printf("Nb_args:%li\n", nb_args);
	if (nb_args > 0)
	{
		new_node->type = AST_COMMAND;
		new_node->cmd.args = malloc((nb_args + 1) * sizeof(char *));
		if (!new_node->cmd.args)
            return ;
		i = 0;
		while (i < nb_args)
		{
			new_node->cmd.args[i++] = ft_strdup((*current)->str);//protect 
			(*current) = (*current)->next;
		}
		new_node->cmd.args[i] = NULL;
	}
	
	i = 0;
	while (i < nb_args)
	{
		printf("cmd elem:%s\n", new_node->cmd.args[i]);
		i++;
	}
	
	// else if (is_operator(type)) 
	// {

	// }
	// else if (is_open_paren(type)) 
	// {
		
	// }
	
}