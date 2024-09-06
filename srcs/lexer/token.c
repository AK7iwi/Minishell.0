/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/06 12:57:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void add_to_token_list(t_token **tokens, uint8_t input_type, char *str) 
{
    t_token *new_node;
    t_token *last;

    new_node = (t_token *)malloc(sizeof(t_token));
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

static  uint8_t wich_token(char *input)
{
    size_t input_len;

    input_len = ft_strlen(input);

    //fct special char + loop
    if (ft_strncmp(input, "|", input_len) == 0)
        return (TOKEN_PIPE);
    else if (ft_strncmp(input, "<", input_len) == 0)
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">", input_len) == 0)
        return (TOKEN_SIMPLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "<<", input_len) == 0)
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">>", input_len) == 0)
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "$", input_len) == 0)
        return (TOKEN_ENV_VARIABLE);
    else if (ft_strncmp(input, "\'", input_len) == 0) 
        return (TOKEN_SIMPLE_QUOTE);
    else if (ft_strncmp(input, "\"", input_len) == 0) 
        return (TOKEN_DOUBLE_QUOTE);
    else if (ft_strncmp(input, "&&", input_len) == 0)
        return (TOKEN_AND);
    else if (ft_strncmp(input, "||", input_len) == 0)
        return (TOKEN_OR);
    else if (ft_strncmp(input, "(", input_len) == 0)
        return (TOKEN_OPEN_PAREN);
    else if (ft_strncmp(input, ")", input_len) == 0)
        return (TOKEN_CLOSE_PAREN);
   
    return (TOKEN_WORD);
}

void   tokenisation(char *input, t_token **tokens)
{
    char** input_array;
	uint8_t token;
	int i;

    input_array = ft_split(input, ' ');
	i = 0;
	
    while (input_array[i])
    {
        token = wich_token(input_array[i]);
        add_to_token_list(tokens, token, input_array[i]);
        i++;
    }
	
	free_array(input_array);
}
