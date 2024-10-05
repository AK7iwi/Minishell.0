/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:17:13 by diguler           #+#    #+#             */
/*   Updated: 2024/10/05 15:17:19 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_pipe_error()
{
    perror("pipe");
    exit(EXIT_FAILURE);
}

void handle_fork_error()
{
    perror("fork");
    exit(EXIT_FAILURE);
}

void handle_exec_error()
{
    perror("exec_cmd");
    exit(EXIT_FAILURE);
}
