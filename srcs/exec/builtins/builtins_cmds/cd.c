/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/05 12:54:58 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool update_env(t_env env, char *cwd)
{
	
	
}

bool	cd(t_data *data, char **args)
{
    char cwd;
    char *dir;
	
	printf("avant cd : ");
	pwd(&data->error);
	
    if (args[1] && args[2])
        return (data->error.exec_errors |= ERROR_CD1, false);
	//protect no_env
	
    if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
        dir = getenv("HOME");
    else if (strcmp(args[1], "-") == 0)
        dir = getenv("OLDPWD");
	else
        dir = args[1];
	
    if (!dir || chdir(dir) != 0)
		return (data->error.exec_errors |= ERROR_CD2, false);
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error->exec_errors |= ERROR_PWD, false);
	else 
   		update_env(data->env, cwd);
	
	printf("\napres cd : ");
	if (!pwd(&data->error))
		return (false);
	
    return (true);
}

