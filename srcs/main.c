#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_env_list *env;
    char *line;

    (void)ac;
    (void)av;
    env = create_env_list(envp);
    line = ft_strdup("echo $USER");
    replace_dollars_in_command(&line, env);
    printf("%s\n", line);
    free(line);
    free_env_list(&env);
    return (0);
}