#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>



int check_type(t_node *node)
{
    if (ft_strcmp(node->token, '<'))
        node->type = rid_in;
    else if (ft_strcmp(node->token, '>'))
        node->type = rid_out;
    else if (ft_strcmp(node->token, '>>'))
        node->type = red_append;
    else if (ft_strcmp(node->token, '<<'))
        node->type = hered;
    else if(ft_strcmp(node->token,'|'))
        node->type = pipe;

    else
        node-type = arg /// handle it can be function or functin with args ... 
    //string skip or default all of them  
}

void token_idtfy(t_node *node)
{
    //check for each toekn 
    //1)_redirection  2)function 3)normal stuff 4)pipe
    while(node)
    {
        check_type(node);
        node = node->next;
    }
}

void printer_ls(t_node *node)
{
    t_node *temp = node;
    while (temp)
    {
        printf(" %s ->aaaa", temp->token);
        temp = temp->next;
    }
    printf(" NULL\n");
}

t_node *create_new_node(char *token)
{
    t_node *new_node;

    if (!token)
        return (NULL);
    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->token = strdup(token);
    if (!new_node->token)
    {
        free(new_node);
        return (NULL);
    }
    new_node->next = NULL;
    return (new_node);
}

void add_in_ls(t_node **ls, char *input)
{ 
    t_node *new_node;
    t_node *temp;

    if (!ls || !input)
        return;
    new_node = create_new_node(input);
    if (!new_node)
        return;
    if (*ls == NULL)
    {
        *ls = new_node;
        return;
    }
    temp = *ls;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

void handle_in_ls(t_node **ls, char *input)
{
    char *token;
    int start = 0, end = 0;

    if (!ls || !input || !*input)
        return;

    while (input[end])
    {
        if (input[end] == ' ' || input[end + 1] == '\0')
        {
            if (input[end + 1] == '\0') 
                end++;
            token = strndup(input + start, end - start);
            if (token)
                add_in_ls(ls, token);
            start = end + 1;
        }
        end++;
    }
}

int main(void)  
{
    char *input = NULL;
    size_t len = 0;
    ssize_t nr;
    t_node *ls = NULL;

    signal(SIGINT, sigint_handler); 

    while (1)
    {
        intro();   
        nr = ftgetline(&input, &len);   
        if (nr < 0)
            break;
        if (nr > 0 && input[nr - 1] == '\n')
            input[nr - 1] = '\0';
        if (nr > 0)
            handle_in_ls(&ls, input);
        printer_ls(ls);
        
        free(input);
        
        input = NULL;
    }

    return (0);
}
