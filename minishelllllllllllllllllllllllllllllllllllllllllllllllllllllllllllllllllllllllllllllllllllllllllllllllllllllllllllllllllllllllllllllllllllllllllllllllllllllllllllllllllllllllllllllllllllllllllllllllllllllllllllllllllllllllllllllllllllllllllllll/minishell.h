#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <stdlib.h>

// typedef struct s_prompt
// {
//     t_list *cmds; //linked list of cmd each node fiya s_mini
//     char **envp; //env variable full 
//     pid_t pid; //proess id of the shell 
// }   t_prompt;

// typedef struct s_mini{
//     char **full_cmd; //store the input ["cecho" "aa" "aaa ",NULL]
//     char **full_path; // fullpa th tt the excutable file 
//     int infile;
//     int outfile; // lama we use the command to write in file adn ge toutput from file 
// }

typedef struct node{
    char *token;
    int n;
    struct node *next;
} t_node;

char * get_next_line(int fd);
void skipswhiteSpaces(char **input);
void handleCd(char *input);
void handleEcho(char *input);
ssize_t	ftgetline(char **lineptr, size_t *n);
void	handle_input(char *input);
void sigint_handler(int sig);
void intro(void);
char	**ft_dup_matrix(char **matrix);
void	ft_free_matrix(char ***matrix);
