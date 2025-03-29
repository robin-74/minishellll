#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
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
//t_elem: la kel token
//t_type: type tabaa l command
//t_env_var: lal env ta asema
//t_cmd_node: la kel command

//int g_signal_received = 0;

// typedef struct s_elem {
// char *token;
// int space_after;
// struct s_elem *next;
// } t_elem;

// //temporary
// typedef enum e_type {
// PIPE,
// SMP_CMD,
// } t_type;

// //split aa ases li aam bekhdo bel env w asemo la 3 parts 1 the key
// //2 the boolean eza le2a = aw lae
// //3 the value li after the =
// typedef struct s_env_var {
// char *key;
// bool equal;
// char *value;
// char *all;
// struct s_env_var *next;
// struct s_env_var *prev;
// } t_env_var;

typedef struct s_cmd_node {
char **arr;
char *in;
char *out;
//t_type type;
char *heredoc;
int append;
int err;
int ex_heredoc;
struct s_cmd_node *next;
} t_cmd_node;

// typedef struct s_exec{
// t_cmd_node *cmd_list;
// t_env_var *env_list;
// int exit_status;
// } t_exec;

	
typedef enum e_token_type {
    COMMAND,
    ARG,
    TOKEN_PIPE,
    RID_IN,
    RID_OUT,
    HERED,
    RED_APPEND
} t_token_type;


typedef struct node{
    char *token;
    int n;
    struct node *next;
    int group;
    struct s_cmd_node *info_node;
   // int pipe_exit =0 ;
    t_token_type type;
} t_node;
void error_msg(char *s,t_node *head);
char * get_next_line(int fd);
void skipswhiteSpaces(char **input);
void handleCd(char *input);
void handleEcho(char *input);
ssize_t	ftgetline(char **lineptr, size_t *n);
void	handle_input(char *input,char **ls);
void sigint_handler(int sig);
void intro(void);
char	**ft_dup_matrix(char **matrix);
void	ft_free_matrix(char ***matrix);
void	free_list(t_node *head);