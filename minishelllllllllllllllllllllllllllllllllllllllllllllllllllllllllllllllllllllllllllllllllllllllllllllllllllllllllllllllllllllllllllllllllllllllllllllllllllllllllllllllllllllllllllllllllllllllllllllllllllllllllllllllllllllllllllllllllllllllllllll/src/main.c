#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void printer_ls(t_node *node)
{
    t_node *temp;

    temp = node;
    while (temp)
    {
        printf(" %s ->", temp->token);
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
    new_node->token = ft_strdup(token);
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
                add_in_ls(ls, token);                                                          +
            start = end + 1;
        }
        end++;
    }
     
}


int	main(void)  
{
	char	*input;
	size_t	len;
	ssize_t	nr;
    t_node *ls;

	input = NULL;
    ls = NULL;
	len = 0;
    signal(SIGINT, sigint_handler);
	while (1)
	{
        intro();
        nr = ftgetline(&input, &len);
        if (nr < -1)
            break;
		if (nr > 0 && input[nr - 1] == '\n')
			input[nr - 1] = '\0';
		if (nr > 0)
			handle_in_ls(&ls, input);
        printer_ls(ls);
		free(input);
		input = NULL;
	}
	free(input);
	return (0);
}
