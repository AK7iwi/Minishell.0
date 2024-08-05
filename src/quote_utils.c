#include "minishell.h"
#include <unistd.h>

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

/*#include "minishell.h"
#include <stdio.h>

int main()
{
    t_data data;
    char *test_cases[] = {
        "This is a 'test",
        "This is a \"test",
        "This is a 'complete' test",
        "This is a \"complete\" test",
        "Mixed 'quotes\" should not affect",
        "Mixed \"quotes' should not affect",
        "Correct 'usage' \"of quotes\" here"
    };

    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
    {
        data.exit_code = 0; // Réinitialiser exit_code avant chaque test
        int result = open_quote(&data, test_cases[i]);
        printf("Test case: %s\n", test_cases[i]);
        printf("Result: %d, exit_code: %d\n\n", result, data.exit_code);
    }

    return 0;
}*/
