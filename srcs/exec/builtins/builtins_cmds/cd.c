/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/06 16:58:47 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool update_env(t_env *env, char *old_cwd)
{
	t_env *current;
	char *cwd;
	
	current = env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	
	while (current)
	{
		if (ft_strncmp(current->str, "PWD=", 4) == 0)
		{
			free(current->str);
			current->str = ft_strjoin("PWD=", cwd);
		}
		else if (ft_strncmp(current->str, "OLDPWD=", 7) == 0)
		{
			free(current->str);
			current->str = ft_strjoin("OLDPWD=", old_cwd);
		}	
		current = current->next;
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
	//protect if (!env)
	//fct dir 
    if (!args[1] || ft_strncmp(args[1], "~", 1) == 0)
        dir = getenv("HOME");
    else if (strcmp(args[1], "-") == 0)
        dir = getenv("OLDPWD");
	else
        dir = args[1];

	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (data->error.exec_errors |= ERROR_CD2, false);
	
    if (!dir || chdir(dir) != 0)
		return (data->error.exec_errors |= ERROR_CD2, false);
	if (update_env(data->env, old_cwd))
		return (data->error.exec_errors |= ERROR_CD2, false);
	
	free(old_cwd);
    return (true);
}

