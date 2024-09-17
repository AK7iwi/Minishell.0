/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/17 14:12:39 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool add_to_token_list(t_token **tokens, uint8_t input_type, char *str) 
{
    t_token *new_node;
    t_token *last;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (EXIT_FAILURE);

    new_node->type = input_type;
    new_node->str = ft_strdup(str);
    new_node->next = NULL;

    if (*tokens == NULL) 
    {
        new_node->prev = NULL;
        *tokens = new_node;  
        return (EXIT_SUCCESS);
    }
    last = *tokens;
    while (last->next)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;

	return (EXIT_SUCCESS);
}

static	uint8_t wich_token(char *str)
{
    if (str[0] == '|' && !str[1])
        return (TOKEN_PIPE);
    else if (str[0] == '<' && !str[1])
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (str[0] == '>' && !str[1])
        return (TOKEN_SIMPLE_REDIRECT_OUT);
    else if (str[0] == '<' && str[1] == '<' && !str[2])
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (str[0] == '>' && str[1] == '>' && !str[2])
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (str[0] == '&' && str[1] == '&' && !str[2])
        return (TOKEN_AND);
    else if (str[0] == '|' && str[1] == '|' && !str[2])
        return (TOKEN_OR);
    else if (str[0] == '(' && !str[1])
        return (TOKEN_OPEN_PAREN);
    else if (str[0] == ')' && !str[1])
        return (TOKEN_CLOSE_PAREN);
   
    return (TOKEN_WORD);
}
inline	bool	is_special_char(char *input, size_t *i)
{
	return (input[*i] == '|' || input[*i] == '<' || input[*i] == '>' || input[*i] == '&');
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
		
		str_token = extract_str(data, input, &token, &i);
		if (!str_token)
			return (EXIT_FAILURE);
		if (!token)
			token = TOKEN_WORD;
		if (ft_strlen(str_token))
			if (add_to_token_list(&data->token, token, str_token))
				return (data->error.error_g |= ERROR_MALLOC, EXIT_FAILURE);
		
		free(str_token);
		
		// str_token = extract_special_char(input, &i, data);
		if (is_special_char(input, &i))
		{
			str_token = "|";
			token = wich_token(str_token);
			if (add_to_token_list(&data->token, token, str_token))
				return (data->error.error_g |= ERROR_MALLOC, EXIT_FAILURE);
		}
		
        i++;
	}
	
	return (EXIT_SUCCESS);
}