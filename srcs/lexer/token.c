#include "minishell.h"

static void print_token_list(t_token *head)
{
    t_token *current = head;

    while (current != NULL)
    {
        printf("Token: %s, Type: %d %s", current->str, current->type, "\n");
        current = current->next;
    }
} 

static void add_to_token_list(t_token **tokens, uint8_t input_type, char *name) 
{
    t_token *new_node;
    t_token *last;

    new_node = (t_token *)malloc(sizeof(t_token));
    if (!new_node)
        return ;

    new_node->type = input_type;
    new_node->str = ft_strdup(name);
    new_node->next = NULL;

    if (*tokens == NULL) 
    {
        new_node->prev = NULL;
        *tokens = new_node;  
        return ;
    }

    last = *tokens;
    while (last->next)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
}

static  uint8_t wich_token(char *input)
{
    size_t input_len;

    input_len = ft_strlen(input);

    //fct special char + loop
    if (ft_strncmp(input, "|", input_len) == 0)
        return (TOKEN_PIPE);
    else if (ft_strncmp(input, "<", input_len) == 0)
        return (TOKEN_SIMPLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">", input_len) == 0)
        return (TOKEN_SIMPLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "<<", input_len) == 0)
        return (TOKEN_DOUBLE_REDIRECT_IN);
    else if (ft_strncmp(input, ">>", input_len) == 0)
        return (TOKEN_DOUBLE_REDIRECT_OUT);
    else if (ft_strncmp(input, "$", input_len) == 0)
        return (TOKEN_ENV_VARIABLE);
    else if (ft_strncmp(input, "\'", input_len) == 0) //test
        return (TOKEN_SIMPLE_QUOTE);
    else if (ft_strncmp(input, "\"", input_len) == 0) //test
        return (TOKEN_DOUBLE_QUOTE);
    else if (ft_strncmp(input, "&&", input_len) == 0)
        return (TOKEN_AND);
    else if (ft_strncmp(input, "||", input_len) == 0)
        return (TOKEN_OR);
    else if (ft_strncmp(input, "(", input_len) == 0)
        return (TOKEN_OPEN_PAREN);
    else if (ft_strncmp(input, ")", input_len) == 0)
        return (TOKEN_CLOSE_PAREN);
   
    return (TOKEN_WORD);
}

void   tokenisation(char *input, t_token *tokens)
{
    char** input_array;

    input_array = ft_split(input, ' ');

    int i = 0;

    while (input_array[i])
    {
        uint8_t token; 
        token = wich_token(input_array[i]);
        
        add_to_token_list(&tokens, token, input_array[i]);
        i++;
    }

    // //test
    print_token_list(tokens);
}
