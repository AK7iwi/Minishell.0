/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 18:35:18 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *compute_expr(t_token **tokens, int min_prec)
{
    // t_ast *result;
    // t_ast *right_side;
    // t_ast_type operator_type;
    // int prec;
    // int assoc;
    // int next_min_prec;

    // result = compute_atom(tokens); //fill_cmd

    // while (cur_token_is_binary_operator(*tokens) && get_prec(*tokens) >= min_prec)
    // {
    //     prec = get_prec(*tokens);    // Récupère la priorité de l'opérateur actuel
    //     assoc = get_assoc(*tokens);  // Récupère l'associativité de l'opérateur
    //     if (assoc == LEFT_ASSOC)
    //         next_min_prec = prec + 1;
    //     else
    //         next_min_prec = prec;

    //     operator_type = (*tokens)->type;  // Capture le type d'opérateur
    //     advance_token(tokens);  // Passe à l'opérateur suivant

    //     // Appel récursif pour traiter le côté droit de l'expression
    //     right_side = compute_expr(next_min_prec, tokens);

    //     // Crée un nœud opérateur dans l'AST
    //     result = create_operator_node(result, right_side, operator_type);
    // }
	
	t_ast 	*result;
	t_token	*current;
	(void)min_prec;
	t_ast *right_side;
	// uint8_t next_min_prec;
	// uint8_t prec;
    // bool 	assoc;
	
	current = (*tokens);

	result = create_node_cmd(tokens);
	printf("Command:\n");
    for (int i = 0; result->cmd.args[i] != NULL; i++)
    {
        printf("Arg[%d]: %s\n", i, result->cmd.args[i]);
    }
	
	// while (is_operator(current->type) && get_prec(current) >= min_prec)
	// {
	// 	printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
	// 	prec = get_prec(current);    
    //     assoc = get_assoc(current);
		
	// 	if (assoc == LEFT_ASSOC) 
    //     	next_min_prec = prec + 1;
    //     else
    //         next_min_prec = prec;
		  
	current = current->next;
	right_side = compute_expr(tokens, 0);
	// 	result = create_operator_node(result, right_side, operator_type);		
	// }
	
    return (result);
}

void 	create_ast(t_data *data)
{
	data->ast = compute_expr(&data->token, 0);
	// compute_expr(&data->token, 0);
}