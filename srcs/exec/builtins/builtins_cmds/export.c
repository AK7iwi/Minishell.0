/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/09 12:58:55 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *copy_var_name(char *args)
{
	char *var_name;
	size_t len;
	
	len = 0;
	
	if (!find_equal(args))
		len = ft_strlen(args);
	else
		while (args[len] != '=')
			len++;
	
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);

	len = 0;
	while (args[len])
	{
		var_name[len] = args[len];
		len++;
	}
	var_name[len] = '\0';
	return (var_name);
}

static bool	is_valid_var(char *var)
{
	size_t i; 
	
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (false);
	
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_') //bug here 
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
		var_name = copy_var_name(args[i]); //protect 
		if (!is_valid_var(var_name))
			printf("export: `%s': not a valid identifier\n", args[i]);
		else if (!getenv(var_name))
			add_env_var(&data->env, args[i]); //protect and free
		else if (find_equal(args[i]))
			set_env_var(&data->env, var_name, args[i]); //protect and free 
		free(var_name);
		i++;
	}
	return (EXIT_SUCCESS);
}