/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/22 19:43:16 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t get_prec(uint8_t type)
{
	if (is_pipe(type))
		return (2);
	else if (is_and(type) || is_or(type))
		return (1);

	return (3);
}

bool get_assoc(uint8_t type)
{
	return (type == TOKEN_PIPE || type == TOKEN_OR || type == TOKEN_AND);
}

t_operator_type get_operator_type(uint8_t type)
{
	t_operator_type operator_type;

	operator_type = 0;
	
	if (is_pipe(type))
		operator_type = AST_PIPE;	
	else if (is_and(type))
		operator_type = AST_AND;
	else if (is_or(type))
		operator_type = AST_OR;

	return (operator_type);
}
t_ast *compute_expr(t_token **tokens, int min_prec)
{
	t_ast 		*result;
	t_ast 		*right_side;
	t_operator_type operator_type;
	uint8_t 	prec;
	uint8_t 	next_min_prec;
	bool 		assoc;
	
	result = create_node_cmd(tokens); //protect
	
	while ((*tokens) && is_operator((*tokens)->type) && get_prec((*tokens)->type) >= min_prec)
	{
		prec = get_prec((*tokens)->type);
		assoc = get_assoc((*tokens)->type);

		if (assoc == 1)
        	next_min_prec = prec + 1;
        else
            next_min_prec = prec;
		
		operator_type = get_operator_type((*tokens)->type);
		(*tokens) = (*tokens)->next;
		
		right_side = compute_expr(tokens, next_min_prec);
		result = create_operator_node(result, right_side, operator_type);
	}
	
    return (result);
}
void 	create_ast(t_data *data)
{
	data->ast = compute_expr(&data->token, 0);
	printf ("AST\n");
	print_ast(data->ast, 0);
}