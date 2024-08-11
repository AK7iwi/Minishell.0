#include "minishell.h"

void quoting_choice(bool *dquote, bool *squote, int *i, char c)
{
    if (c == '\'' && !(*dquote)) 
        *squote = !(*squote); 
    else if (c == '\"' && !(*squote)) 
        *dquote = !(*dquote);
    (*i)++;
}

int open_quote(t_data *data, char *line) 
{
    bool squote = false;
    bool dquote = false;
    int i = 0;

    while (line[i])
        quoting_choice(&dquote, &squote, &i, line[i]);

    if (squote || dquote) 
    {
        data->exit_code = 2;
        write(STDERR_FILENO, "minishell: syntax error: open quote\n", 36);
        return (1);
    }
    return (0);
}