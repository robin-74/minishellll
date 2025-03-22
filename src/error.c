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