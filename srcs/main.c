#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    // t_env_list *env;
    // char *line;

    t_token tokens;

    tokens = (t_token){0};
    
    char *input;

    (void)ac;
    (void)av;
    (void)envp;

    while (1)
    {
        input = readline("minishell> ");
        
		//test
        printf("input: %s\n", input);
		
        tokenisation(input, &tokens);
        //free token 
    }
    
    // env = create_env_list(envp);
    // line = ft_strdup("echo $USER");
    // replace_dollars_in_command(&line, env);
    // printf("%s\n", line);
    // free(line);
    // free_env_list(&env);
    
    return (0);
}