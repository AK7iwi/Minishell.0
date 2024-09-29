/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:31:32 by diguler           #+#    #+#             */
/*   Updated: 2024/09/29 13:45:22 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getline(void)
{
    char *line;
    size_t i;
    int ch;

    line = malloc(BUFFER_SIZE);
    if (!line)
        return (NULL);
    i = 0;
    while (i < BUFFER_SIZE - 1)
    {
        ch = getchar();
        if (ch == EOF)
            break;
        if (ch == '\n')
            break;
		line[i] = (char)ch;
		i++;
    }
	line[i] = '\0';
	if (i == 0 && ch == EOF)
    {
        free(line);
        return (NULL);
    }
	return (line);
}
void write_to_file(int output_fd, const char *line)
{
    write(output_fd, line, ft_strlen(line));
    write(output_fd, "\n", 1);
}
int open_output_file(const char *output_file)
{
    int output_fd;
	
	output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return output_fd;
}

