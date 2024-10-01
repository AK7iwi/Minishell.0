/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:53:36 by diguler           #+#    #+#             */
/*   Updated: 2024/10/01 15:21:28 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child_process(int output_fd, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline(">");
        if (!line)
            break;
		if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
		write_to_file(output_fd, line);
        free(line);
    }
    close(output_fd);
    exit(EXIT_SUCCESS);
}


void create_heredoc(char *delimiter)
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



