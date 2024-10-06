/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/06 16:48:35 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool update_env(t_env **env, char *old_cwd)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	
	while (*env)
	{
		if (ft_strncmp((*env)->str, "PWD=", 4) == 0)
		{
			free((*env)->str);
			(*env)->str = ft_strjoin("PWD=", cwd);
		}
		else if (ft_strncmp((*env)->str, "OLDPWD=", 7) == 0)
		{
			free((*env)->str);
			(*env)->str = ft_strjoin("OLDPWD=", old_cwd);
		}
		
		(*env) = (*env)->next;
	}
	
	free(cwd);
	
	return (EXIT_SUCCESS);
}
bool	cd(t_data *data, char **args)
{
    char *old_cwd;
    char *dir;
	
	if (args[1] && args[2])
		return (data->error.exec_errors |= ERROR_CD1, false);
	
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (data->error.exec_errors |= ERROR_CD2, false);
	
    if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
        dir = getenv("HOME");
    else if (strcmp(args[1], "-") == 0)
        dir = getenv("OLDPWD");
	else
        dir = args[1];
	
    if (!dir || chdir(dir) != 0)
		return (data->error.exec_errors |= ERROR_CD2, false);
	if (update_env(&data->env, old_cwd))
		return (data->error.exec_errors |= ERROR_CD2, false);
	
	free(old_cwd);
	
    return (true);
}

