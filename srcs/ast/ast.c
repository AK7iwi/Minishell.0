/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:25:53 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/21 16:22:51 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *compute_expr(int min_prec, t_token **tokens)
{
    t_ast *result;
    t_ast *right_side;
    t_ast_type operator_type;
    int prec;
    int assoc;
    int next_min_prec;

    result = compute_atom(tokens); // Traite l'atome

    while (cur_token_is_binary_operator(*tokens) && get_prec(*tokens) >= min_prec)
    {
        prec = get_prec(*tokens);    // Récupère la priorité de l'opérateur actuel
        assoc = get_assoc(*tokens);  // Récupère l'associativité de l'opérateur
        if (assoc == LEFT_ASSOC)
            next_min_prec = prec + 1;
        else
            next_min_prec = prec;

        operator_type = (*tokens)->type;  // Capture le type d'opérateur
        advance_token(tokens);  // Passe à l'opérateur suivant

        // Appel récursif pour traiter le côté droit de l'expression
        right_side = compute_expr(next_min_prec, tokens);

        // Crée un nœud opérateur dans l'AST
        result = create_operator_node(result, right_side, operator_type);
    }

    return (result);
}