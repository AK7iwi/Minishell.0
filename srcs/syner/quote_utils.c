#include "minishell.h"

void quoting_choice(bool *dquote, bool *squote, int *i, char c)
{
    if (c == '\'' && !(*dquote)) 
        *squote = !(*squote); 
    else if (c == '\"' && !(*squote)) 
        *dquote = !(*dquote);
    (*i)++;
}

bool open_quote(char *line) 
{
    bool open_squote;
    bool open_dquote;
    int i;
	
	open_dquote = false;
	open_squote = false;

	i = 0;

    while (line[i])
	{
		printf("line[i]:%c%c", line[i],'\n');
    	quoting_choice(&open_dquote, &open_squote, &i, line[i]);
	}
	
	return (open_squote || open_dquote);
}