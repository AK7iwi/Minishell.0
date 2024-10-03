/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfeldman <mfeldman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:08:47 by diguler           #+#    #+#             */
/*   Updated: 2024/10/03 17:34:10 by mfeldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd sans arguments -> home
// cd avec arguments -> deplacer vers arguments
// sauvegarder le PWD actuel pour modifier le OLDPWD de l'environnement
// modifier le PWD de l'environnement apres avoir bouger de path
// cd avec plus d'un arguments -> error
// cd ~ -> retour au home
// cd - -> a verifie
// proteger les chdir 

t_env_list *find_env_var(t_env_list *env, const char *name)
{
    size_t name_len = strlen(name);
    while (env)
    {
        if (strncmp(env->str, name, name_len) == 0 && env->str[name_len] == '=')
            return (env);
        env = env->next;
    }
    return (NULL);
}

int update_env_var(t_env_list *env, const char *name, const char *new_value)
{
    t_env_list *var;
    
    var = find_env_var(env, name);
    if (var)
    {
        free(var->str);
        var->str = malloc(strlen(name) + strlen(new_value) + 2);
        if (!var->str)
        {
            printf("Error: failed to allocate memory for environment variable '%s'\n", name);
            return (1);
        }
        strcpy(var->str, name);
        strcat(var->str, "=");
        strcat(var->str, new_value);
        return (0);
    }
    printf("Error: environment variable '%s' not found\n", name);
    return (1);
}


int ft_update_pwd(char *new_pwd, t_env_list *env)
{
    char old_pwd[1024];
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
        return (1); 
    if (update_env_var(env, "OLDPWD", old_pwd)) 
        return (1);
    return update_env_var(env, "PWD", new_pwd);
}

bool	cd(char **args, t_env_list *env)
{
    char cwd[1024];
    char *dir;
	
	printf("avannt cd : ");
	pwd();
    if (args[1] && args[2])
    {
        printf("cd: too many arguments\n");
        return (1);
    }
    if (!args[1] || strcmp(args[1], "~") == 0)
        dir = getenv("HOME");
    else if (strcmp(args[1], "-") == 0)
        dir = getenv("OLDPWD");
    else
        dir = args[1];
    if (!dir || chdir(args[0]) != 0)
    {
        perror("cd");
        return (1);
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
   {     ft_update_pwd(cwd, env);}
	printf("\napres cd : ");
	pwd();
    return (0);
}

