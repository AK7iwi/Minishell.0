/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:48 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/09 14:34:01 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *	extract_str(char *input, size_t start, size_t end, size_t quotes_cnt)
{
	char *str; 
	size_t i;
	
	str = (char *)malloc((end - start- quotes_cnt) + 1);
	if (!str)
		return (NULL);

	i = 0;
	while (start < end)
	{
		if (input[i] != "\'" || input[i] != "\"")
		{
			str[i] = input[start];
			start++;
		}
			
		i++;
	}
	
	str[i] = '\0';
	
	return (str);
}

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

uint8_t wich_token(char *input)
{
    size_t input_len;

    input_len = ft_strlen(input);
	
    // loop on special char
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

bool	tokenisation(char *input, t_token **tokens)
{
	uint8_t		token;
	char 		*str;
	size_t		i;
	size_t		start;
	size_t		end;
	size_t		quotes_cnt;
	// char quote;
	
	i = 0;
	
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		
		start = i;
		
		while (input[i] != ' ' && input[i] != '\0')
		{
			//handle_quotes
			if (input[i] == ''' || input[i] == ")
				quotes_cnt++;
			i++;
		}
		
		end = i;
		
		printf("len : %li\n", end - start - quotes_cnt);
		
		str = extract_str(input, start, end, quotes_cnt);
		
		token = wich_token(str);
		add_to_token_list(tokens, token, str);
			
		printf("str: %s \n", str);
		free(str);
		
		//fct handle quote
		// if (input[i] == "\'" || input[i] == "\"")
		// {
		// 	quote = input[i];
		// 	i++;
		// 	while (input[i] != quote && input[i] != '\0')
		// 	{
		// 		str += input[i];
		// 		i++;
		// 	}
		// 	token = TOKEN_WORD;
		// 	add_to_token_list(tokens, token, str);
		// }
		
		// str += input[i];
		// i++;
	}
	
	return (EXIT_SUCCESS);
}
