#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "libft.h"   
int	ft_getlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	ft_free_matrix(char ***matrix)
{
	int	i;

	if (!matrix || !(*matrix))
		return;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

char	**ft_dup_matrix(char **matrix)
{
	char	**ans;
	int		i;
	int		len;

	if (!matrix)
		return (NULL);
	len = ft_getlen(matrix);
	ans = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ans)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		ans[i] = ft_strdup(matrix[i]);
		if (!ans[i])
		{
			ft_free_matrix(&ans);
			return (NULL);
		}
		i++;
	}
	ans[i] = NULL;
	return (ans);
}