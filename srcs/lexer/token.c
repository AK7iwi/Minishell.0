/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/14 17:39:26 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void add_to_token_list(t_token **tokens, uint8_t input_type, char *str) 
{
    t_token *new_node;
    t_token *last;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return ;

    new_node->type = input_type;
    new_node->str = ft_strdup(str);
    new_node->next = NULL;

    if (*tokens == NULL) 
    {
        new_node->prev = NULL;
        *tokens = new_node;  
        return ;
    }
    last = *tokens;
    while (last->next)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
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

bool	tokenisation(char *input, t_token **tokens)
{
	char 		*str;
	uint8_t		token;
	size_t		i;
	
	str = NULL;
	i = 0;
	
	while (i < ft_strlen(input))
	{
		token = 0;
		str = extract_str(input, &token, &i);
		if (!str)
			return (EXIT_FAILURE);
		
		if (!token)
			token = wich_token(str);
		
		add_to_token_list(tokens, token, str);
		free(str);
        i++;
	}
		
	return (EXIT_SUCCESS);
}