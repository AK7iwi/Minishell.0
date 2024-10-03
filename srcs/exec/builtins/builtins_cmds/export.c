/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:05:00 by diguler           #+#    #+#             */
/*   Updated: 2024/09/28 12:45:03 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

//sans arguments -> afficher les variables triees
//si variable sans = -> export avec valeur vide si elle n'exite pas
//si variable avec = -> cree/mettre a jour la variable
//variable invalide -> erreur sans modif l'environnement

int	is_valid_var(char *str)
{
	int i; 
	
	i = 0;
	
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_env_list *env)
{
	t_env_list *tmp; 
	
	tmp = env;
	
	while (tmp)
	{
		if (ft_strchr(tmp->str, '='))
			printf("export %s\n", tmp->str);
		else
			printf("export %s\n", tmp->str);
		tmp = tmp->next;
	}
}
void set_env_var(char *var, t_env_list *env)
{
    t_env_list *current; 
    int len; 
	
	current = env;
	len = ft_strlen(var);

    while (current) 
    {
        if (ft_strncmp(current->str, var, len) == 0 && current->str[len] == '=')
        {
            free(current->str);
            current->str = ft_strdup(var);
            return;
        }
        current = current->next;
    }
    append_env_list(&env, var, "");
}

int	ft_export(char **args, t_env_list *env)
{
	int i;
	
	i = 1;

	if (!args[1])
	{
		print_export(env);
		return (0);
	}

	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("export: `%s': not a valid identifier\n", args[i]);
		else if (ft_strchr(args[i], '='))
			set_env_var(args[i], env); 
		else
		{
			if (!get_env_value(args[i], env))
				append_env_list(&env, args[i], "");
		}
		i++;
	}
	return (0);
}