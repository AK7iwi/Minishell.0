/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/09/29 12:13:09 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gérer les redirections (pipes et fichiers)
// Gérer les processus enfants et les commandes internes
// Gérer les erreurs et les signaux
// Optimiser la libération des ressources et la modularité du code

void	exec_command(char **env, t_cmd *cmd)
{
	char	*path;
	char	**find_the_path;

	find_the_path = find_path(env);
	path = valid_path(find_the_path, cmd->args[0]);
	if (execve(path, cmd->args, env) == -1)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		free_tab(find_the_path);
		exit(EXIT_FAILURE);
	}
}


void exec_pipeline(t_cmd **cmds, char **env)
{
    int tube[2];
    pid_t pid;
    int fd_in = 0;
    int i = 0;

    while (cmds[i] != NULL)
    {
        if (cmds[i + 1] != NULL)
            create_pipe(tube);
        pid = fork();
        handle_fork(pid, env, cmds[i], fd_in, tube);
        if (pid > 0)
        {
            wait(NULL);
            close(tube[1]);
            if(fd_in != 0)
                close(fd_in);
            fd_in = tube[0];
        }
        i++;
    }
}
