#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void intro()
{
    write(1,"\nminishell> ",12);
}
void skipswhiteSpaces(char **input)
{
    while(**input == ' ')
    {
        (*input)++;
    };
}
//case /cd we go back to the orinal directiory
//case cd/... we go the directory 

void handleCd(char *input)
{
    char *dir;
    char cwd[1020];

        if (ft_strncmp(input, "cd", 2) != 0)
            return;
        input += 2;
        skipswhiteSpaces(&input);
        if (ft_strlen(input) == 0) // /cd o back home
        {
            dir = getenv("HOME");
            if (!dir)
            {
                ft_printf("Error in home directory handle default home");
                return;
            }

        }
        else if(ft_strncmp(input,"..",2)==0)
            dir = "..";
        else 
            dir= input;
        
        if (chdir(dir) == -1) //if we could not change teh directry using chdir 
        {
            ft_printf("Error in chmid ");
            return;
        };
        if (getcwd(cwd,1024)!= NULL)
            setenv("PWD", cwd, 1);
        else
            ft_printf("error minisehll in settign the cwd ");
}

void handleEcho(char *input)
{
    int print_nl = 1;

        if (ft_strncmp(input, "echo", 4) == 0)
        {
            input += 4;
            skipswhiteSpaces(&input);
            if (ft_strncmp(input, "-n", 2) == 0)
            {
                print_nl = 0;
                input += 2;
                skipswhiteSpaces(&input);
            };
            ft_printf("%s",input);
            if (print_nl)
            {
                write(1, "\n",1);
            }
        }
}
ssize_t	ftgetline(char **lineptr, size_t *n)
{
	size_t	i;
	char	buffer[2000];
	ssize_t	bytes_read;
	ssize_t	i;

	i = 0;
	if (!*lineptr )
    {
        if (!(*lineptr = malloc(90000)))
            return -(1);
        *n = 128;
    }
	while (1)
	{
		bytes_read = read(STDIN_FILENO, buffer, 1999);
		if (bytes_read <= 0)
			return (-1);//handle case ctrl D 0 return 0 
		buffer[bytes_read] = 0;
		i = 0;
		while (i < bytes_read)
		{
			(*lineptr)[i] = buffer[i];
			if (buffer[i++] == '\n')
				return ((*lineptr)[i + 1] = 0) + i + 1;
			i++;
		}
	}
}

void	handle_input(char *input)
{
	if (!ft_strncmp(input, "exit", 4) || !ft_strncmp(input, "a", 1))
	{
		free(input);
		exit(0);
	}
    // handleEcho(input);
    // handleCd(input);
	ft_printf("entered : ->  ");
	write(1, input, ft_strlen(input));
	write(1, "\n", 1);
}
void sigint_handler(int sig)
{
     (void)sig;
     write(1,"\nminishell> ",12);
}