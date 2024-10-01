/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:31:32 by diguler           #+#    #+#             */
/*   Updated: 2024/10/01 14:42:13 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

