/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:56:27 by diguler           #+#    #+#             */
/*   Updated: 2024/09/29 11:22:47 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_pipe(int *tube)
{
    if (pipe(tube) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void setup_redirections(int fd_in, int *tube)
{
    if (fd_in != 0)
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (tube[1] != -1)
    {
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
    }
    close(tube[0]);
}

void handle_fork(pid_t pid, char **env, t_cmd *cmd, int fd_in, int *tube)
{
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        setup_redirections(fd_in, tube);
        exec_command(env, cmd);
        exit(EXIT_FAILURE);
    }
}
