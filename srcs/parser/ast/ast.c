/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/08 14:59:24 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t get_prec(t_tok_type type)
{
	//verif
	if (is_pipe(type))
		return (1);
	else if (is_and(type) || is_or(type))
		return (2);

	return (3);
}

t_op_type get_operator_type(t_tok_type type)
{
	t_op_type operator_type;

	operator_type = 0; //verif 
	
	if (is_pipe(type))
		operator_type = AST_PIPE;	
	else if (is_and(type))
		operator_type = AST_AND;
	else if (is_or(type))
		operator_type = AST_OR;

	return (operator_type);
}

t_ast *ast_cmd_and_subsh_handler(t_token **current)
{
	t_ast *new_node;
	
	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	
	if ((*current) && (*current)->type == TOKEN_OPEN_PAREN)
		new_node = subsh_node_creator(&new_node, current);
	else
		new_node = node_cmd_creator(&new_node, current);

	return (new_node);
}

void	ast_op_handler(t_ast **result, t_token **current, uint8_t min_prec)
{
	uint8_t 	next_min_prec;
	t_op_type	op_type;
	t_ast 		*right_side;
	
	while ((*current) && is_operator((*current)->type) && get_prec((*current)->type) >= min_prec)
	{
		next_min_prec = get_prec((*current)->type); //verif if assoc
		op_type = get_operator_type((*current)->type);
		(*current) = (*current)->next;
		right_side = ast_algo(current, next_min_prec);
		(*result) = operator_node_creator((*result), right_side, op_type); // protect
	}
}
t_ast *ast_algo(t_token **current, uint8_t min_prec)
{
	t_ast 		*result;
	
	result = ast_cmd_and_subsh_handler(current);
	if (!result)
    	return (NULL);
	if ((*current) && (*current)->type == TOKEN_CLOSE_PAREN)
		return (result);
	ast_op_handler(&result, current, min_prec); // protect

    return (result);
}
bool	ast_creator(t_data *data)
{
	t_token *current;
	current = data->token;
	data->ast = ast_algo(&current, 0);

	return (!data->ast);
}