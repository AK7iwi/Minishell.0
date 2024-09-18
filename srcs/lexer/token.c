/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/18 13:31:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool add_to_token_list(t_token **token, uint8_t *str_type, char *str) 
{
    t_token *new_node;
    t_token *last;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (EXIT_FAILURE);

    new_node->type = (*str_type);
    new_node->str = ft_strdup(str);
    new_node->next = NULL;

    if (*token == NULL) 
    {
        new_node->prev = NULL;
        *token = new_node;  
        return (EXIT_SUCCESS);
    }
    last = *token;
    while (last->next)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;

	return (EXIT_SUCCESS);
}

bool	add_token(t_token **token_struct, uint8_t *token, char *str_token)
{
	if (ft_strlen(str_token))
		if (add_to_token_list(token_struct, token, str_token))
			return (EXIT_FAILURE);
	free(str_token);

	return (EXIT_SUCCESS);
}
uint8_t wich_token(char *str_token)
{
    if (str_token[0] == '|' && !str_token[1])
        return (TOKEN_PIPE);
    else if (str_token[0] == '<' && !str_token[1])
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (str_token[0] == '>' && !str_token[1])
        return (TOKEN_SIMPLE_REDIRECT_OUT);
	else if (str_token[0] == '$')
        return (TOKEN_ENV_VAR);
    else if (str_token[0] == '<' && str_token[1] == '<' && !str_token[2])
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (str_token[0] == '>' && str_token[1] == '>' && !str_token[2])
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (str_token[0] == '&' && str_token[1] == '&' && !str_token[2])
        return (TOKEN_AND);
    else if (str_token[0] == '|' && str_token[1] == '|' && !str_token[2])
        return (TOKEN_OR);
    else if (str_token[0] == '(' && !str_token[1])
        return (TOKEN_OPEN_PAREN);
    else if (str_token[0] == ')' && !str_token[1])
        return (TOKEN_CLOSE_PAREN);
	else if (str_token[0] == ')' && !str_token[1])
        return (TOKEN_CLOSE_PAREN);

    return (0);
}
bool	tokenisation(t_data *data, char *input)
{
	char 		*str_token;
	uint8_t		token;
	size_t		i;
	
	str_token = NULL;
	i = 0;
	
	while (i < ft_strlen(input))
	{	
		token = 0;

		if (handle_str(data, input, &token, &i))
			return (EXIT_FAILURE);
		if (handle_special_char(data, input, &token, &i))
			return (EXIT_FAILURE);
	}
	
	return (EXIT_SUCCESS);
}