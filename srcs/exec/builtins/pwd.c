/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:28:19 by diguler           #+#    #+#             */
/*   Updated: 2024/09/29 20:40:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if(!cwd)
		printf("pwd error"); //msg error
	else
		printf("%s\n", cwd);
}