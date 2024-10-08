/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/10/08 11:57:20 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//sans arguments -> afficher les variables triees dans l'ordre alphabetique, d'abord les majuscules ensuite les minuscules
//si variable sans = -> export avec valeur vide si elle n'exite pas
//si variable avec = -> cree/mettre a jour la variable
//variable invalide -> erreur sans modif l'environnement

// static void set_env_var(char *var, t_env_list *env)
// {
//     t_env_list *current; 
//     int len; 
	
// 	current = env;
// 	len = ft_strlen(var);

//     while (current) 
//     {
//         if (ft_strncmp(current->str, var, len) == 0 && current->str[len] == '=')
//         {
//             free(current->str);
//             current->str = ft_strdup(var);
//             return ;
//         }
//         current = current->next;
//     }
//     append_env_list(&env, var, "");
// }


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

static bool	print_sorted_env(t_env *env)
{
	char	**cpy_env;
	size_t 	i;
	
	cpy_env = copy_env(env);
	if (!cpy_env)
		return (EXIT_FAILURE);
	
	sort_env(cpy_env);
	
	i = 0;
	while (cpy_env[i])
	{
		printf("export %s\n", cpy_env[i]);
		i++;
	}
	
	free(cpy_env);
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