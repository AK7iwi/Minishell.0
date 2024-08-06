/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diguler <diguler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:47:53 by diguler           #+#    #+#             */
/*   Updated: 2024/08/06 16:25:25 by diguler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//malloc la liste
t_token *list_initialize()
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->str = NULL;
    token->type = 0;
    token->prev = NULL;
    token->next = NULL;
    return token;
}
void add_node_end(t_token **head, char *str, int type)
{
    t_token *new_node = malloc(sizeof(t_token));
    if (!new_node)
        return;

    new_node->str = str;
    new_node->type = type;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        t_token *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}


void   token(char *input)
{
    t_token *token;
    char *str;
    int i;
    int j;
    i = 0;
    j = 0;
    list_initialize(token);
    while(input[i])
    {
        if(input[i] == INPUT)
        {
            add_node_end(&token, "<", INPUT);
            i++;
        }
        else if(input[i] != INPUT)
        {
            while(input[i] != INPUT || input[i] != HEREDOC || input[i] != TRUNC || input[i] != APPEND || input[i] != PIPE)
            {
                i++;
            }
        }
        
    }
}