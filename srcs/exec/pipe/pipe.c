/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:41:20 by diguler           #+#    #+#             */
/*   Updated: 2024/10/01 15:19:33 by diguler          ###   ########.fr       */
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
}void create_heredoc(char *delimiter)
{
    pid_t pid;
    int tube[2];

    if (pipe(tube) == -1)  // Créer un tube pour communiquer entre parent et enfant
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork(); // Créer un nouveau processus
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // Processus enfant
    {
        close(tube[0]); // Fermer l'extrémité de lecture du tube
        child_process(tube[1], delimiter); // Gérer la logique de lecture jusqu'au délimiteur
        close(tube[1]); // Fermer l'extrémité d'écriture une fois terminé
        exit(EXIT_SUCCESS);
    }
    else // Processus parent
    {
        close(tube[1]); // Fermer l'extrémité d'écriture du tube
        wait(NULL); // Attendre la fin de l'enfant
        // À ce stade, le parent peut lire l'entrée du tube via tube[0] si nécessaire
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
