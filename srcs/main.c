/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:03:03 by mfeldman          #+#    #+#             */
/*   Updated: 2024/10/01 12:41:26 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struct(t_data *data)
{
	data->error.error_g = 0;
	data->token = NULL;
	data->ast = NULL;
	data->env = NULL;
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
	
	init_struct(&data);
	if (is_arg(&data.error, argc))
		return (msg_error(data.error), EXIT_FAILURE);
	
    while (1)
    {
        input = readline("Minishell> "); //protect input
		if (!input)
			return (free_loop(&data), EXIT_FAILURE);
        if (tokenizer(&data, input) || syn_analyzer(&data) || ast_creator(&data)) //parse fct
			msg_error(data.error);
		else if (init_env(&data, envp) || ast_exec(&data, data.ast)) //exec fct
			msg_error(data.error);
		
		// print_token_list(data.token);
		// print_ast(data.ast, 0);
		
		free_loop(&data);
    }
	
    return (EXIT_SUCCESS);
}
