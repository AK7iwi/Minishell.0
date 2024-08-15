#include "minishell.h"

static bool is_a_cmd(char *input)
{
    if (ft_strncmp(input, "echo", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "cd", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "pwd", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "export", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "unset", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "env", ft_strlen(input)) == 0)
        return (true);
    else if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
        return (true);
    
    return (false);
}

static int wich_token(char *input)
{
    if (is_a_cmd(input))
        return (TOKEN_COMMAND);
    else if (ft_strncmp(input, "|", ft_strlen(input)) == 0)
        return (TOKEN_PIPE);
    else if (ft_strncmp(input, "<", ft_strlen(input)) == 0)
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">", ft_strlen(input)) == 0)
        return (TOKEN_SIMPLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "<<", ft_strlen(input)) == 0)
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">>", ft_strlen(input)) == 0)
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "$", ft_strlen(input)) == 0)
        return (TOKEN_ENV_VARIABLE);
    else if (ft_strncmp(input, "\'", ft_strlen(input)) == 0)
        return (TOKEN_SIMPLE_QUOTE);
    else if (ft_strncmp(input, "\"", ft_strlen(input)) == 0)
        return (TOKEN_DOUBLE_QUOTE);
    else if (ft_strncmp(input, "&&", ft_strlen(input)) == 0)
        return (TOKEN_AND);
    else if (ft_strncmp(input, "||", ft_strlen(input)) == 0)
        return (TOKEN_OR);
    else if (ft_strncmp(input, "(", ft_strlen(input)) == 0)
        return (TOKEN_OPEN_PAREN);
    else if (ft_strncmp(input, ")", ft_strlen(input)) == 0)
        return (TOKEN_CLOSE_PAREN);
    else   
        return (TOKEN_ARGUMENT);
    
    return (0);
}

static void print_token_list(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
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
        token = wich_token(input_array[i]);

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
