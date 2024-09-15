/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 16:42:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_token_list(t_token *head)
{
    t_token *current = head;
		
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}

static void	init_struct(t_data *data)
{
	data->error.error_g = 0;
	data->token = NULL;
}

static inline bool is_arg(int argc, t_error *error)
{
	if (argc != 1)
	{
		error->error_g |= ERROR_ARG;
		return (true);
	}

	return (false);
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argv;
    (void)envp; //tmp
	
	init_struct(&data);
	
	if (is_arg(argc, &data.error))
		return (msg_error(data.error), EXIT_FAILURE);
	
    while (1)
    {
        //protect input
        input = readline("Minishell> ");
		if (!input)
			return (free_all(&data), EXIT_FAILURE);
		
		//parsing 
        if (tokenisation(input, &data.token)) //|| !parse_tokens(&data.token)
		{
			msg_error(data.error);
			free_all(&data);
		}
		
		print_token_list(data.token);
    	free_token(&data.token);
    }
	
	free_all(&data);
	
    return (EXIT_SUCCESS);
}