#include "minishell.h"

static int wich_token(char *input)
{
    if (ft_strncmp(input, "|", ft_strlen(input)) == 0)
        return (TOKEN_PIPE);
    else if (ft_strncmp(input, "<", ft_strlen(input)) == 0)
        return (TOKEN_REDIRECT_IN);
    else if (ft_strncmp(input, ">", ft_strlen(input)) == 0)
        return (TOKEN_REDIRECT_OUT);
    else if (ft_strncmp(input, ">", ft_strlen(input)) == 0)
        return (TOKEN_REDIRECT_OUT);
    
    return (0);
}

static void print_token_list(t_token *head)
{
    t_token *current = head;
    printf("NOOOOOOOOOOOOOOOON\n");
    while (current != NULL)
    {
        printf("OUIIIIIII");
        printf("Token: %s, Type: %d, %s", current->str, current->type, "\n");
        current = current->next;
    }

    printf("A LA FIN\n");
}

//work but not clean
static void append_token_list(t_token *tokens, int i_type, char *name) //utils certainly 
{
    //node -->token

    t_token *new_node = (t_token *)malloc(sizeof(t_token));
    t_token *last = tokens;

    if (!new_node)
        return ;

    new_node->type = i_type;
    new_node->str = ft_strdup(name);
    new_node->next = NULL;
    if (tokens == NULL) 
    {
        new_node->prev = NULL;
        tokens = new_node;
        return ;
    }
    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
}

static void add_input_to_list(char **input_array, t_token *tokens)
{    
    int i = 0;

    while (input_array[i])
    {
        int token;
        printf("%i%s", i, ":");
        printf("%s\n", input_array[i]);
        token = wich_token(input_array[i]);

        printf("TOKEN:%d", token);

        append_token_list(tokens, token, input_array[i]);
        i++;
    }
}

static inline char**   split_input(char *input)
{
    return (ft_split(input, ' '));
}

void   tokenisation(char *input, t_token *tokens)
{
    char** input_array;

    input_array = split_input(input);
    
    add_input_to_list(input_array, tokens);
    //test
    print_token_list(tokens);
}
