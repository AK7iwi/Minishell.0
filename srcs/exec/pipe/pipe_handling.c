/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:16:41 by diguler           #+#    #+#             */
/*   Updated: 2024/10/05 15:16:45 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_pipe_creation(int tube[2])
{
    if (pipe(tube) == -1)
        handle_pipe_error();
}

void redirect_output(int tube[2])
{
    dup2(tube[1], STDOUT_FILENO); 
    close(tube[0]); 
    close(tube[1]);
}

void redirect_input(int fd_in)
{
    dup2(fd_in, STDIN_FILENO); 
    close(fd_in);
}
