/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/07 10:49:33 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool update_dir(t_env *env, char *old_cwd) //handle diffrent errors 
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
			if (!set_env_var(current, "PWD=", cwd))
				return (EXIT_FAILURE);
		}
		else if (ft_strncmp(current->str, "OLDPWD=", 7) == 0)
		{
			if (!set_env_var(current, "OLDPWD=", old_cwd))
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
static bool	set_dir(char **dir, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 1) == 0)
        (*dir) = getenv("HOME");
    else if (ft_strncmp(arg, "-", 1) == 0)
        (*dir) = getenv("OLDPWD");
	else
        (*dir) = arg;

	return ((*dir));
}
bool	cd(t_data *data, char **args)
{
    char *old_cwd;
    char *dir;
	
	//protect if (!env)
	if (args[1] && args[2])
		return (data->error.exec_errors |= ERROR_CD1, EXIT_FAILURE);
	
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd || !set_dir(&dir, args[1]) || chdir(dir))
		return (data->error.exec_errors |= ERROR_CD2, EXIT_FAILURE);
	if (update_dir(data->env, old_cwd))
		return (data->error.exec_errors |= ERROR_CD2, EXIT_FAILURE);
	
	free(old_cwd);
    return (EXIT_SUCCESS);
}

