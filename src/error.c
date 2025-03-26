 #include "../minishell.h"

void	free_list(t_node *head)
{
	t_node *temp;

	while (head)
	{
		temp = head->next;
		free(head->token);
		free(head);
		head = temp;
	}
}

void error_msg(char *s,t_node *head)
{
    printf("error with %s",s);
    free_list(head);
    exit(1);
}