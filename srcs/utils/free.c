/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:02:39 by mfeldman          #+#    #+#             */
/*   Updated: 2024/09/15 18:23:19 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	free_token(t_token **tokens)
{
	t_token	*tmp;
	t_token	*current;

	if (!(*tokens))
		return ;
	current = *tokens;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	*tokens = NULL;
}

static inline void 	free_error(t_error *error)
{
	error->error_g = 0;
}

void	free_loop(t_data *data)
{
	if (data->error.error_g)
		free_error(&data->error);
	if (data->token)
		free_token(&data->token);
}

void	free_all(t_data *data)
{
	if (data->token)
		free_token(&data->token);
}