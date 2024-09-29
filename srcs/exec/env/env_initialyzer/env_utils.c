#include "minishell.h"

void free_env_list(t_env_list **lst)
{
    t_env_list *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->str);
        free(*lst);
        *lst = tmp;
    }
}
char *get_env_value(char *var, t_env_list *env) 
{
    t_env_list *current = env;

    while (current) 
    {
        if (ft_strncmp(current->str, var, ft_strlen(var)) == 0 && current->str[ft_strlen(var)] == '=')
            return (current->str + ft_strlen(var) + 1);  // +1 pour sauter le '='
        current = current->next;
    }

    return (NULL);
}

char *extract_var_name(char *str, int *i) 
{
    int start = *i + 1;
    
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')) 
        (*i)++;

    return (ft_substr(str, start, *i - start));
}

char *replace_env_vars(char *line, t_env_list *env) 
{
    int i = 0;
    char *result = ft_strdup("");
    char *var_name;
    char *var_value;
    char *temp;
    char *new_result;

    while (line[i]) 
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_')) 
        {
            var_name = extract_var_name(line, &i);
            var_value = get_env_value(var_name, env);
            if (var_value) 
            {
                new_result = ft_strjoin(result, var_value);
                free(result);
                result = new_result;
            }
            free(var_name);
        } 
        else 
        {
            temp = ft_substr(line, i, 1);
            new_result = ft_strjoin(result, temp);
            free(result);
            free(temp);
            result = new_result;
            i++;
        }
    }
    return (result);
}

void replace_dollars_in_command(char **line, t_env_list *env) 
{
    char *new_line = replace_env_vars(*line, env);
    free(*line);
    *line = new_line;
}

void append_env_list(t_env_list **lst, char *str)
{
    t_env_list *new_node = (t_env_list *)malloc(sizeof(t_env_list));
    t_env_list *last = *lst;

    if (!new_node)
        return;
    new_node->str = str;
    new_node->next = NULL;
    if (*lst == NULL) 
    {
        new_node->prev = NULL;
        *lst = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
}
t_env_list *create_env_list(char **envp) 
{
    t_env_list *env = NULL;
    int i = 0;

    while (envp[i]) 
    {
        append_env_list(&env, ft_strdup(envp[i]));
        i++;
    }
    return (env);
}