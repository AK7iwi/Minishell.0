/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:53:36 by diguler           #+#    #+#             */
/*   Updated: 2024/09/29 13:44:56 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_heredoc(int fd, const char *delimiter)
{
    char *line;

    while (1)
    {
        printf("> ");
        line = ft_getline();
        if (line == NULL)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        if (write(fd, line, ft_strlen(line)) == -1)
        {
            perror("write");
            free(line);
            break;
        }
        free(line);
    }
}

void child_process(int output_fd, const char *delimiter)
{
    char *line;

    while (1)
    {
        line = ft_getline();
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


void create_heredoc(const char *delimiter, const char *output_file)
{
    pid_t pid;
    int output_fd;

    output_fd = open_output_file(output_file);
    if (output_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
	pid = fork();
    if (pid == -1)
    {
        perror("fork");
        close(output_fd);
        exit(EXIT_FAILURE);
    }
	if (pid == 0)
    {
        child_process(output_fd, delimiter);
    }
    else
    {
        close(output_fd);
        wait(NULL);
    }
}


