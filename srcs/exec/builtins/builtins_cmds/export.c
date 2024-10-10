/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/10 15:41:42 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_var_value(char *args)
{
	char *var_value;
	size_t len;
	size_t i;
	size_t j;

	i = 0;
	while (args[i] != '=')
		i++;
	i++;
	len = 0;
	while (args[i + len])
		len++;

	var_value = malloc(len + 1);
	if (!var_value)
		return (NULL);

	j = 0;
	while (j < len)
	{
		var_value[j] = args[i + j];
		j++;
	}
	var_value[j] = '\0';
	return (var_value);
}
static char *extract_var_name(char *args)
{
	char *var_name;
	size_t len;
	size_t i;
	
	len = 0;
	while (args[len] != '=')
		len++;
	
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);

	i = 0;
	while (i < len)
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
	char *var_name;
	char *var_value;
	
	sort_env(&current);
	
	while (current)
	{
		var_name = extract_var_name(current->str);
		var_value = extract_var_value(current->str);
		printf("export %s=\"%s\"\n", var_name, var_value);
		free(var_name);
		free(var_value);
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
		else if (find_equal(args[i]))
		{
			//fct 
			var_name = extract_var_name(args[i]); //protect 
			if (!get_my_env(data->env, var_name))
				add_env_var(&data->env, args[i]); //protect 
			else
				set_env_var(&data->env, var_name, args[i]); //protect and free
			free(var_name);
		}
		//else
			//mark for subshell
		i++;
	}
	return (EXIT_SUCCESS);
}