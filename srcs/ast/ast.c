/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/25 16:43:21 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t get_prec(uint8_t type)
{
	if (is_pipe(type))
		return (1);
	else if (is_and(type) || is_or(type))
		return (2);

	return (3);
}
bool get_assoc(uint8_t type)
{
	return (type == TOKEN_PIPE || type == TOKEN_OR || type == TOKEN_AND);
}

t_op_type get_operator_type(uint8_t type)
{
	t_op_type operator_type;

	operator_type = 0; //!! verif 
	
	if (is_pipe(type))
		operator_type = AST_PIPE;	
	else if (is_and(type))
		operator_type = AST_AND;
	else if (is_or(type))
		operator_type = AST_OR;

	return (operator_type);
}
t_ast *ast_algo(t_token *current, int min_prec)
{
	t_ast 		*result;
	t_ast 		*right_side;
	t_op_type	op_type;
	uint8_t 	prec;
	bool 		assoc;
	uint8_t 	next_min_prec;

	if (current->type == TOKEN_OPEN_PAREN)
		result = create_subsh_node(&current);
	else
	{
		result = create_node_cmd(&current);
		if (!result)
    		return (NULL);
	}
	if (current && current->type == TOKEN_CLOSE_PAREN)
	{
		current = current->next;
		return (result);
	}
	
	if (current)
		printf("Current:%s\n", current->str);
			
	while (current && is_operator(current->type) && get_prec(current->type) >= min_prec)
	{
		prec = get_prec(current->type);
		assoc = get_assoc(current->type);

		if (assoc == 1)
        	next_min_prec = prec + 1;
        else
        next_min_prec = prec;
		
		op_type = get_operator_type(current->type);
		current = current->next;
		
		right_side = ast_algo(current, next_min_prec);
		result = create_operator_node(result, right_side, op_type);
	}
	
    return (result);
}
void 	create_ast(t_data *data)
{
	t_token *current;
	current = data->token;
	data->ast = ast_algo(current, 0);
	if (data->ast)
	{
		printf ("AST:\n");
		print_ast(data->ast, 0);
	}
}