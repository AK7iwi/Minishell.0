/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/09 11:49:30 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *copy_var_name(char *args)
{
	char *var_name;
	size_t i;

	i = 0;
	while (args[i] != '=')
		i++;

	var_name = malloc(i + 1);

	while (args[i] != '=')
	{
		var_name[i] = args[i];
		i++;
	}
	var_name[i] = '\0';

	return (var_name);
}

static bool	is_valid_var(char *var)
{
	size_t i; 
	
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (false);
	
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	
	return (true);
}
static void	sort_env(t_env **env)
{
	bool swapped;
    t_env *current;
	char *temp;
	
	swapped = true;
	
    while (swapped)
    {
        swapped = false;
        current = *env;

        while (current->next)
        {
            if (strcmp(current->str, current->next->str) > 0) //ft_strcmp
            {
				temp = current->str;
    			current->str = current->next->str;
    			current->next->str = temp;
                swapped = true;
            }
            current = current->next;
        }
    }
}
static bool	print_sorted_env(t_env *env)
{
	t_env *current;
	current = env;
	
	sort_env(&current);
	
	while (current)
	{
		printf("export %s\n", current->str);
		current = current->next;
	}
	
	return (EXIT_SUCCESS);
}
bool	ft_export(t_data *data, char **args)
{
	size_t i;
	char *var_name;

	if (!args[1])
		if (print_sorted_env(data->env))
			return (EXIT_FAILURE);
		
	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("export: `%s': not a valid identifier\n", args[i]);
		else if (!getenv(args[i]))
			add_env_var(&data->env, args[i]);
		else if (find_equal(args[i]))
		{
			var_name = copy_var_name(args[i]);
			set_env_var(&data->env, var_name, args[i]);
			free(var_name);
		}
		i++;
	}
	
	return (EXIT_SUCCESS);
}