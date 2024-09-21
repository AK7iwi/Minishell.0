/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 19:16:45 by mfeldman         ###   ########.fr       */
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
	return (type = TOKEN_PIPE);
}
t_ast *compute_expr(t_token **tokens, int min_prec)
{
	t_ast 	*result;
	t_token	*current;
	t_ast 	*right_side;
	uint8_t next_min_prec;
	uint8_t prec;
    bool 	assoc;
	
	current = (*tokens);

	result = create_node_cmd(tokens);
	
	while (is_operator(current->type) && get_prec(current->type) >= min_prec)
	{
		prec = get_prec(current->type);    
        assoc = get_assoc(current->type);
		
		if (assoc != 0) 
        	next_min_prec = prec + 1;
        else
            next_min_prec = prec;
		  
	current = current->next;

	right_side = compute_expr(tokens, next_min_prec);
	result = create_operator_node(result, &current, right_side);
	
	}
	
    return (result);
}

void print_ast(t_ast *ast, int level)
{
    if (!ast) return; // Check if the AST node is NULL

    // Indent based on the depth of the node
    for (int i = 0; i < level; i++)
        printf("    "); // Indentation for better readability

    if (ast->type == AST_COMMAND)
    {
        printf("Command:\n");
        for (int i = 0; ast->cmd.args[i] != NULL; i++)
        {
            printf("%*sArg[%d]: %s\n", level * 4, "", i, ast->cmd.args[i]); // Indentation for args
        }
    }
    else if (ast->type == AST_OPERATOR)
    {
        printf("%*sOperator: %d\n", level * 4, "", ast->operator.type); // Adjust format for operator
        // Recursively print left and right children
        print_ast(ast->operator.left, level + 1);
        print_ast(ast->operator.right, level + 1);
    }
    // Handle other node types if necessary
}

void 	create_ast(t_data *data)
{
	data->ast = compute_expr(&data->token, 0);
	print_ast(data->ast, 0);
	// compute_expr(&data->token, 0);
}