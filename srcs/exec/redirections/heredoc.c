/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:53:36 by diguler           #+#    #+#             */
/*   Updated: 2024/10/09 15:34:40 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child_process(int output_fd, char *delimiter)
{
    char *line;
    (void)output_fd;
    int file = open(delimiter, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
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
		write_to_file(file, line);
        free(line);
    }
    close(file);
    exit(EXIT_SUCCESS);
}


void create_heredoc(char *delimiter)
{
    pid_t pid;
    int tube[2];

    if (pipe(tube) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(tube[0]);
        child_process(tube[1], delimiter);
        close(tube[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(tube[1]); 
        wait(NULL);
    }
}



