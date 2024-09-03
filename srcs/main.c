#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    // t_env_list *env;
    // char *line;

    if (argc != 1)
    {
        printf("Get your arguments out of the way");
        return (EXIT_FAILURE);
    }

    t_token tokens;

    tokens = (t_token){0};
    
    char *input;

    (void)argv;
    (void)envp;

    while (1)
    {
        input = readline("Minishell> ");
	
        tokenisation(input, &tokens);
        //free token 
    }
    
    return (EXIT_SUCCESS);
}