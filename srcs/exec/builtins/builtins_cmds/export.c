/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/09 09:28:26 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//sans arguments -> afficher les variables triees dans l'ordre alphabetique, d'abord les majuscules ensuite les minuscules
//si variable sans = -> export avec valeur vide si elle n'exite pas
//si variable avec = -> cree/mettre a jour la variable
//variable invalide -> erreur sans modif l'environnement

static bool	is_valid_var(char *str)
{
	size_t i; 
	
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	
	return (true);
}
static void swap_env_var(t_env *current, t_env *current_n)
{
	char *temp;

	temp = current->str;
    current->str = current_n->str;
    current_n->str = temp;
}
static void	sort_env(t_env **env)
{
	bool swapped;
    t_env *current;
	
	if (*env == NULL || (*env)->next == NULL)
		return ;
	
	swapped = true;
	
    while (swapped)
    {
        swapped = false;
        current = *env;

        while (current->next)
        {
            if (strcmp(current->str, current->next->str) > 0) //ft_strcmp
            {
                swap_env_var(current, current->next);
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
	
	if (!args[1])
		if (print_sorted_env(data->env))
			return (EXIT_FAILURE);
		
	i = 1;

	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("export: `%s': not a valid identifier\n", args[i]);
		// else if (ft_strchr(args[i], '='))
		// 	set_env_var(args[i], env); 
		// else
		// {
		// 	if (!get_env_value(args[i], env))
		// 		append_env_list(&env, args[i], "");
		// }
		i++;
	}
	
	return (EXIT_SUCCESS);
}