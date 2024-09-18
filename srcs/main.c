/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/18 14:16:03 by mfeldman         ###   ########.fr       */
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

static inline bool is_arg(t_error *error, int argc)
{
	if (argc != 1)
		return (error->error_g |= ERROR_ARG, true);

	return (false);
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*input;

	(void)argv;
    (void)envp; //tmp
	
	init_struct(&data);
	
	if (is_arg(&data.error, argc))
		return (msg_error(data.error), EXIT_FAILURE);
	
    while (1)
    {
        input = readline("Minishell> "); //protect input
		if (!input)
			return (free_all(&data), EXIT_FAILURE); // error
        if (tokenisation(&data, input) || parse_tokens(&data))
			msg_error(data.error);
		print_token_list(data.token);
		free_loop(&data);
    }
	
    return (free_all(&data), EXIT_SUCCESS);
}
