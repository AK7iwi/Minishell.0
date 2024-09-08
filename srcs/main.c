/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/08 18:57:13 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token_list(t_token *head)
{
    t_token *current = head;
		
    while (current)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
}

void	init_struct(t_data *data)
{
	data->token = NULL;
	data->error = NULL;
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
    (void)envp; //tmp

	t_data	data;
	char	*input;

	init_struct(&data);
	
    if (argc != 1)
    {
        printf("Get your arguments out of the way");
        return (EXIT_FAILURE);
	}
	
    while (1)
    {
        input = readline("Minishell> ");
		if (!input)
			return (free_all(&data), EXIT_FAILURE);
		
        if (tokenisation(input, &data.token))
			return (free_all(&data), EXIT_FAILURE);
		print_token_list(data.token);
		// if (parsing(data.token))
		// 	return (free_all(&data), EXIT_FAILURE);
    	free_token(&data.token);
    }
	
	free_all(&data);
	
    return (EXIT_SUCCESS);
}